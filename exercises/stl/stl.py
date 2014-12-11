#!/usr/bin/env python

import sys

WORDS = ['professionalism', 'respect', 'perseverance']

def read_n_and_message(f):
    n = int(f.readline())
    message = f.readline().lower()
    return n, message

def scan_message(n, message, word):
    groups = []
    group = ''
    n_counter = 0
    for c in message:
        if c in word:
            group += c
            n_counter = 0
        else:
            n_counter += 1
        if n_counter > n:
            groups.append(group)
            group = ''
            n_counter = 0
    if group != '':
        groups.append(group)
    return groups

def word_in_groups(groups, word):
    for group in groups:
        if sorted(group) == sorted(word):
            return True
    return False

def main():
    n, message = read_n_and_message(sys.stdin)
    
    for word in WORDS:
        groups = scan_message(n, message, word)
        if word_in_groups(groups, word):
            print 'True'
            return
    print 'False'

if __name__ == '__main__':
    main()
