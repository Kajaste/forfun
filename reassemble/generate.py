#!/usr/bin/env python

import random
import sys


def main():
    sentence = sys.argv[1]
    num_of_fragments = int(sys.argv[2])

    for _ in xrange(num_of_fragments):
        begin = random.randint(0, len(sentence) - 2)
        end = random.randint(begin + 1,
                             min(begin + 10, len(sentence)))
        print '{%s}' % (sentence[begin:end])

if __name__ == '__main__':
    main()
