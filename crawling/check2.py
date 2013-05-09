#! /usr/bin/python
# -*- coding: utf-8 -*-

import sys
import codecs

def main ():
    if len(sys.argv) != 3:
        print "Usage: %s inputFile wordFile" %sys.argv[0]
        sys.exit (1)

    ifile = codecs.open (sys.argv[1], 'r', encoding='utf-8')
    wfile = codecs.open (sys.argv[2], 'r', encoding='utf-8')
    words = wfile.readlines ()

    for k, iline in enumerate(l.strip() for l in ifile):
        if k % 1000 == 0: print >> sys.stderr, k

        for i, wline in enumerate(l.strip() for l in words):
            #print "%s in %s" %(wline.encode ('utf8'), iline.encode ('utf8'))
            if  iline in wline:
                break
        else:
            print iline.encode ('utf8')

    ifile.close ()
    wfile.close ()

if __name__ == "__main__":
    main ()
