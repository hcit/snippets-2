#! /usr/bin/python
# -*- coding: utf-8 -*-

import sys
import codecs
import myanmar.language as ml

def main ():
    if len(sys.argv) != 2:
        print "Usage: %s inputFile" %sys.argv[0]
        sys.exit (1)

    ifile = codecs.open (sys.argv[1], 'r', encoding='utf-8')
    ofile = codecs.open (sys.argv[1] + '.fixed', 'w',encoding='utf-8')

    def progress (num):
        if (num % 10000) == 0:
            print num

    i = 0
    for line in (l.strip() for l in ifile):
        i += 1
        progress (i)

        #line = ml.normalize (line)
        for i, ch in enumerate(line):
            # Strip non-myanmar letters
            if not ml.ismyanmar (ch) or ml.ismydigit (ch) or ml.ismypunct (ch):
                line = line.replace (ch, '')

        if line:
            ofile.write (line + '\n')

    ifile.close ()
    ofile.close ()

if __name__ == "__main__":
    main ()
