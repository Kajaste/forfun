#!/usr/bin/python

import sys

def read_n(f):
    return int(f.readline())

def is_even(n):
    return n % 2 == 0

def iterate(n):
    largest = n
    while n != 1:
        if is_even(n):
            n = n / 2
        else:
            n = 3 * n + 1
        if n > largest:
            largest = n
    return largest

def main():
    n = read_n(sys.stdin)
    largest = iterate(n)
    print largest

if __name__ == '__main__':
    main()
