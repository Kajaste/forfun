#!/usr/bin/env python3

import string
import sys

FINNISH_LETTERS = frozenset('abcdefghijklmnopqrstuvwxyzåäö')


class Word:
    def __init__(self, w):
        self.word = w
        self.letters = frozenset(self.word) & FINNISH_LETTERS

    def __repr__(self):
        return self.word


def main(argv):
    if len(argv) != 2 or argv[1] in ('-h', '--help'):
        print('USAGE: %s TEXTFILE' % (argv[0]))
        sys.exit(1)

    print_most_muhku_wordpairs(get_most_muhku_wordpairs(get_words(argv[1])))


def print_most_muhku_wordpairs(wordpairs):
    print('\n'.join(sorted((str(wordpair) for wordpair in wordpairs))))


def get_most_muhku_wordpairs(words):
    pairs, max_muhku, i = [], 0, 0
    words = sorted(words, key=lambda x: len(x.letters), reverse=True)
    for w1 in words:
        if len(w1.letters) * 2 < max_muhku:
            break
        i += 1
        for w2 in words[i:]:
            if len(w1.letters) + len(w2.letters) < max_muhku:
                break
            m = len(w1.letters | w2.letters)
            if m < max_muhku:
                continue
            elif m > max_muhku:
                pairs = [(w1, w2)]
                max_muhku = m
            else:
                pairs.append((w1, w2))
    return pairs


def get_words(filename):
    with open(filename) as source_file:
        words = frozenset(w.strip(string.punctuation).lower()
                          for w in source_file.read().split())
    return (Word(w) for w in words)

if __name__ == '__main__':
    main(sys.argv)
