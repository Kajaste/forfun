#!/usr/bin/env python

import sys

def main():
    def loop(row, n):
        if row == 0:
            print (n -1)*' ' + '*'
        elif row == n*2 -2:
            print (n-1)*' ' + '*'
            return
        elif row < n:
            print (n -1 -row) * ' ' + '*' + (1 + 2*(row -1))*' ' + '*'
        else:
            print (row -n +1) * ' ' + '*' + ((2*n -3) - 2*(row - n +1))*' ' + '*'
        loop(row +1, n)
        
    n = int(sys.stdin.readline())
    if n <= 0:
        return
    if n == 1:
        print '*'
    else:
        loop(0, n)
    
if __name__ == '__main__':
    main()
