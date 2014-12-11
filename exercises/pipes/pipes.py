#!/usr/bin/env python

import sys

END = '#'
XING = '+'
HPIPE = '-'
VPIPE = '|'

def read_lines(f):
    lines = [line.rstrip() for line in f
             if len(line.rstrip()) != 0]
    return lines

def find_ends(lines):
    ends = []
    for linenum, line in enumerate(lines):
        for colnum, char in enumerate(line):
            if char == END:
                ends.append((linenum, colnum))
    return ends

def end_is_possible(lines, vpos, hpos, ends):
    if (vpos, hpos + 1) in ends:
        ends.remove((vpos, hpos + 1))
    elif (vpos, hpos - 1) in ends:
        ends.remove((vpos, hpos - 1))
    elif (vpos + 1, hpos) in ends:
        ends.remove((vpos + 1, hpos))
    elif (vpos - 1, hpos) in ends:
        ends.remove((vpos - 1, hpos))
    else:
        return False
    return True

def walk_pipes(lines, ends):
    max_len = 0
    while len(ends) != 0:
        walked = set([])
        walked_len = 1
        vpos, hpos = ends.pop()
        while True:
            if lines[vpos][hpos + 1] in (HPIPE, XING) and not (vpos, hpos + 1) in walked:
                hpos += 1
            elif lines[vpos][hpos - 1] in (HPIPE, XING) and not (vpos, hpos - 1) in walked:
                hpos -= 1
            elif lines[vpos + 1][hpos] in (VPIPE, XING) and not (vpos + 1, hpos) in walked:
                vpos += 1
            elif lines[vpos - 1][hpos] in (VPIPE, XING) and not (vpos - 1, hpos) in walked:
                vpos -= 1
            elif end_is_possible(lines, vpos, hpos, ends):
                if walked_len + 1 > max_len:
                    max_len = walked_len + 1
                break
            else:
                continue
            walked_len += 1
            walked.add((vpos, hpos))
                
    return max_len

def main():
    lines = read_lines(sys.stdin)
    ends = find_ends(lines)
    print walk_pipes(lines, ends)

if __name__ == '__main__':
    main()
