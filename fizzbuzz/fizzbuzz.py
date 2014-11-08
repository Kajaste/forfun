#!/usr/bin/env python

'''
Baby code solution for Fizz Buzz
'''

import sys


def main():
    ''' Get the number of items to print or tell the user to provide it '''
    try:
        print fizzbuzz(int(sys.argv[1]))
    except (IndexError, ValueError):
        print 'Usage: %s <UINT>' % (sys.argv[0])


def test():
    ''' Test that the solution works as intended '''
    expected_36 = '1, 2, Fizz, 4, Buzz, Fizz, 7, 8, Fizz, Buzz, 11, Fizz, ' \
    '13, 14, Fizz Buzz, 16, 17, Fizz, 19, Buzz, Fizz, 22, 23, Fizz, Buzz, ' \
    '26, Fizz, 28, 29, Fizz Buzz, 31, 32, Fizz, 34, Buzz, Fizz'

    assert fizzbuzz(36) == expected_36


def fizzbuzz(how_many):
    ''' Construct the result string '''
    return ', '.join([fizz_buzz_or_fizzbuzz(i)
                      for i in xrange(1, how_many + 1)])


def fizz_buzz_or_fizzbuzz(number):
    ''' Pick Fizz, Buzz, FizzBuzz or just the number '''

    def divisible_by(divisor):
        ''' Check whether the number is divisible by the divisor or not '''
        return number % divisor == 0

    if divisible_by(15):
        return 'Fizz Buzz'
    elif divisible_by(3):
        return 'Fizz'
    elif divisible_by(5):
        return 'Buzz'
    else:
        return str(number)


if __name__ == '__main__':
    test()
    main()
