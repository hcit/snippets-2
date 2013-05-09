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
    ofile = codecs.open (sys.argv[1] + '.pcol', 'w',encoding='utf-8')

    for line in ( l.strip() for l in ifile):
        for c in ml.ClusterIter(line):
            ofile.write ("%s " %c)
        ofile.write ('\n')

    ifile.close ()
    ofile.close ()

if __name__ == "__main__":
    main ()
