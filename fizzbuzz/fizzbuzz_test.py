#!/usr/bin/env python

import unittest
import fizzbuzz


class DefaultWidgetSizeTestCase(unittest.TestCase):
    def runTest(self):
        ''' Test that the solution works as intended '''

        expected_36 = '1, 2, Fizz, 4, Buzz, Fizz, 7, 8, Fizz, Buzz, 11, ' \
        'Fizz, 13, 14, Fizz Buzz, 16, 17, Fizz, 19, Buzz, Fizz, 22, 23, ' \
        'Fizz, Buzz, 26, Fizz, 28, 29, Fizz Buzz, 31, 32, Fizz, 34, Buzz, Fizz'

        self.assertEqual(fizzbuzz.fizzbuzz(36), expected_36)


if __name__ == '__main__':
    unittest.main()
