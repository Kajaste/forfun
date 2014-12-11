#!/usr/bin/env python

NTH = ['', 'first', 'second', 'third', 'fourth', 'fifth', 'sixth',
       'seventh', 'eighth', 'ninth', 'tenth', 'eleventh', 'first']

STUFFS = ['12 Drummers Drumming',
          '11 Pipers Piping',
          '10 Lords a Leaping',
          '9 Ladies Dancing',
          '8 Maids a Milking',
          '7 Swans a Swimming',
          '6 Geese a Laying',
          '5 Golden Rings',
          '4 Calling Birds',
          '3 French Hens',
          '2 Turtle Doves',
          'A Partridge in a Pear Tree']

def do_it():
    string = ''
    strings = []
    for n in range(1, 13):
        string += 'On the %s day of Christmas\nmy true love sent to me:' % (NTH[n])
        string += '\n' + '\n'.join(STUFFS[-n:])
        strings.append(string)
        string = ''
        STUFFS[-1] = 'and a Partridge in a Pear Tree'
    return strings

def main():
    print '\n\n'.join(do_it())

if __name__ == '__main__':
    main()
