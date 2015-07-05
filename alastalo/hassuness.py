#!/usr/bin/env python3

from itertools import groupby
import string
import sys

FINNISH_VOWELS = set('aeiouyäö')


def main(argv):
    if len(argv) != 2 or argv[1] in ('-h', '--help'):
        print('USAGE: %s TEXTFILE' % (argv[0]))
        sys.exit(1)

    print_most_hassu_words(get_most_hassu_words(get_words(argv[1])))


def print_most_hassu_words(words_with_hassus):
    print('\n'.join(sorted([word_hassu[0] for word_hassu in words_with_hassus
                            if word_hassu[1] == words_with_hassus[0][1]])))


def get_most_hassu_words(words):
    return sorted([(word, compute_hassu(word)) for word in words],
                  key=lambda x: x[1], reverse=True)


def compute_hassu(word):
    hassu = 0
    for k, g in groupby(word, lambda x: x in FINNISH_VOWELS):
        if k:
            streak = len(list(g))
            hassu += streak * 2**streak
    return hassu


def get_words(filename):
    with open(filename) as source_file:
        return set((word.strip(string.punctuation)
                    for word in source_file.read().split()))


def sanity_check():
    assert compute_hassu('koira') == 10
    assert compute_hassu('hääyöaie') == 896

if __name__ == '__main__':
    sanity_check()
    main(sys.argv)

