#!/usr/bin/env python

import sys


def fizz_buzz_or_fizzbuzz(number):
    divisible_by_3 = not number % 3
    divisible_by_5 = not number % 5

    if divisible_by_3 and divisible_by_5:
        return 'Fizz Buzz'
    elif divisible_by_3:
        return 'Fizz'
    elif divisible_by_5:
        return 'Buzz'
    else:
        return str(number)


def fizzbuzz(how_many):
    return ', '.join([fizz_buzz_or_fizzbuzz(i)
                      for i in xrange(1, how_many + 1)])


def main():
    try:
        print fizzbuzz(int(sys.argv[1]))
    except (IndexError, ValueError):
        print 'Usage: %s <UINT>' % (sys.argv[0])


def test():
    EXPECTED_36 = '1, 2, Fizz, 4, Buzz, Fizz, 7, 8, Fizz, Buzz, 11, Fizz, ' \
    '13, 14, Fizz Buzz, 16, 17, Fizz, 19, Buzz, Fizz, 22, 23, Fizz, Buzz, ' \
    '26, Fizz, 28, 29, Fizz Buzz, 31, 32, Fizz, 34, Buzz, Fizz'

    assert fizzbuzz(36) == EXPECTED_36


if __name__ == '__main__':
    test()
    main()
