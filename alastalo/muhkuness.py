#!/usr/bin/env python3

import string
import sys

FINNISH_LETTERS = frozenset('abcdefghijklmnopqrstuvwxyzåäö')


class Word:
    def __init__(self, w):
        self.word = w.strip(string.punctuation).lower()
        self.letters = frozenset(w) & FINNISH_LETTERS

    def __eq__(self, other):
        return self.word.__eq__(other.word)

    def __hash__(self):
        return self.word.__hash__()

    def __repr__(self):
        return self.word.__repr__()


def main(argv):
    if len(argv) != 2 or argv[1] in ('-h', '--help'):
        print('USAGE: %s TEXTFILE' % (argv[0]))
        sys.exit(1)

    print_most_muhku_wordpairs(get_most_muhku_wordpairs(get_words(argv[1])))


def print_most_muhku_wordpairs(wordpairs):
    print('\n'.join(sorted((str(wordpair) for wordpair in wordpairs))))


def get_most_muhku_wordpairs(words):
    pairs = []
    muhku = 0
    words = sorted(words, key=lambda x: len(x.letters), reverse=True)
    i = 0
    for w1 in words:
        if len(w1.letters) * 2 < muhku:
            break
        i += 1
        for w2 in words[i:]:
            m = len(w1.letters | w2.letters)
            if m < muhku:
                if len(w1.letters) + len(w2.letters) < muhku:
                    break
                continue
            elif m > muhku:
                pairs = [(w1, w2)]
                muhku = m
            else:
                pairs.append((w1, w2))
    return pairs


def get_words(filename):
    with open(filename) as source_file:
        return frozenset(Word(w) for w in source_file.read().split())


if __name__ == '__main__':
    main(sys.argv)
