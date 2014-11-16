#!/usr/bin/env python

'''
Tests for Fizz Buzz
'''

import unittest
import fizzbuzz


class FizzBuzzTestCase(unittest.TestCase):
    ''' Test case for Fizz Buzz '''

    def test_word_pick(self):
        ''' Test that correct output is picked for numbers '''
        self.assertEqual(fizzbuzz.fizz_buzz_or_fizzbuzz(1), '1')
        self.assertEqual(fizzbuzz.fizz_buzz_or_fizzbuzz(3), 'Fizz')
        self.assertEqual(fizzbuzz.fizz_buzz_or_fizzbuzz(4), '4')
        self.assertEqual(fizzbuzz.fizz_buzz_or_fizzbuzz(5), 'Buzz')
        self.assertEqual(fizzbuzz.fizz_buzz_or_fizzbuzz(14), '14')
        self.assertEqual(fizzbuzz.fizz_buzz_or_fizzbuzz(15), 'Fizz Buzz')
        self.assertEqual(fizzbuzz.fizz_buzz_or_fizzbuzz(16), '16')

    def test_string_construction(self):
        ''' Test that output string is constructed correctly '''
        expected_36 = '1, 2, Fizz, 4, Buzz, Fizz, 7, 8, Fizz, Buzz, 11, ' \
        'Fizz, 13, 14, Fizz Buzz, 16, 17, Fizz, 19, Buzz, Fizz, 22, 23, ' \
        'Fizz, Buzz, 26, Fizz, 28, 29, Fizz Buzz, 31, 32, Fizz, 34, Buzz, Fizz'
        self.assertEqual(fizzbuzz.fizzbuzz(36), expected_36)


def main():
    ''' Set up the framework with tests and run them '''
    runner = unittest.TextTestRunner()
    suite = unittest.makeSuite(FizzBuzzTestCase, 'test')
    runner.run(suite)


if __name__ == '__main__':
    main()
