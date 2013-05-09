b#! /usr/bin/python
# -*- coding: utf-8 -*-

import sys
import codecs

def main ():
    if len(sys.argv) != 2:
        print "Usage: %s inputFile" %sys.argv[0]
        sys.exit (1)

    ifile = codecs.open (sys.argv[1], 'r', encoding='utf8')
    ofile = codecs.open (sys.argv[1] + '.fixed', 'w',encoding='utf8')

    def is_myanmar_number (char):
        return char >= u'၀' and char <= u'၉'

    for line in ifile.readlines ():
        line = line.strip ()
        chars_to_strip = u'၊။.-)"\',('

        for c in chars_to_strip:
            #print c
            line = line.replace (c, u'')

        if line and is_myanmar_number (line[0]):
            continue

        line = line.replace (u'၀', u'ဝ')
        #line = line.replace ('၀', 'ဝ')

        ofile.write (line + '\n')

    ifile.close ()
    ofile.close ()

if __name__ == "__main__":
    main ()
