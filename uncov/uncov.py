#!/usr/bin/env python

import os
import shlex
import sys
from subprocess import Popen, PIPE


def run_command(cmd):
    return Popen(shlex.split(cmd), stdout=PIPE, stderr=PIPE).communicate()[0]


def get_interesting_files(directory):
    files = [f for f in os.listdir(directory)
             if os.path.isfile(os.path.join(directory, f))]

    files = [os.path.join(directory, f) for f in files
             if f.endswith('.c') or
             f.endswith('.gcda') or
             f.endswith('.gcno') or
             f.endswith('.gcov')]

    return files


def generate_gcov_files(directory):
    files = get_interesting_files(directory)
    curdir = os.path.abspath(os.curdir)
    os.chdir(os.path.abspath(directory))
    for f in [os.path.basename(f) for f in files if f.endswith('.c')]:
        run_command('gcov -i {}'.format(f))
    os.chdir(curdir)


def get_skipped_files(directory):
    def notefile_missing(f):
        notefile = os.path.splitext(f)[0] + '.gcno'
        return not os.path.isfile(notefile)

    files = get_interesting_files(directory)
    return sorted([f for f in files
                   if f.endswith('.c') and notefile_missing(f)])


def analyze_skipped_files(skipped_files):
    def count_lines(f_obj):
        return len([l for l in f_obj if len(l.strip()) != 0])

    result = {}
    for f in skipped_files:
        with open(f) as f_obj:
            result[f] = count_lines(f_obj)

    return result


def get_compiled_files(directory):
    def notefile_found(f):
        notefile = os.path.splitext(f)[0] + '.gcno'
        return os.path.isfile(notefile)

    files = get_interesting_files(directory)
    return [f for f in files if f.endswith('.c') and notefile_found(f)]


def analyze_compiled_files(compiled_files):
    result = {}
    for f in compiled_files:
        gcovfile = f + '.gcov'
        with open(gcovfile) as f_obj:
            total, skipped = 0, 0
            for l in f_obj:
                if l.startswith('lcount:'):
                    total += 1
                    if l.rstrip().endswith(',0'):
                        skipped += 1
            result[f] = (total, skipped)

    return result


def count_totals(result, result_compilee):
    total, skipped = 0, 0
    for r in result.itervalues():
        total += r
        skipped += r

    for rc in result_compilee.itervalues():
        total += rc[0]
        skipped += rc[1]

    return total, skipped


def main(argv):
    directory = argv[1]

    generate_gcov_files(directory)
    skipped_files = get_skipped_files(directory)

    result = analyze_skipped_files(skipped_files)

    compiled_files = get_compiled_files(directory)
    result_compilee = analyze_compiled_files(compiled_files)

    total, skipped = count_totals(result, result_compilee)

    print 'Completely uncovered files:\n{}'.format('\n'.join(skipped_files))
    print
    print '{} lines out of {} skipped'.format(skipped, total)
    print
    print 'Coverage {} %'.format(float(total - skipped) / total * 100)

if __name__ == '__main__':
    main(sys.argv)
