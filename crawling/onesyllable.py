#! /usr/bin/python
# -*- coding: utf-8 -*-

import sys
import codecs
import myanmar.language as ml
import nltk
import itertools

def main ():
    if len(sys.argv) != 2:
        print "Usage: %s inputFile" %sys.argv[0]
        sys.exit (1)

    ifile = codecs.open (sys.argv[1], 'r', encoding='utf-8')

    for k, line in enumerate(( l.strip() for l in ifile)):
        #print line.encode ('utf8')
        try:
            syllables = list(ml.ClusterIter(line))
        except:
            pass
        if len(syllables) == 1 and u'\u1039' not in syllables[0]:
            print "".join(syllables).encode ('utf8')
    ifile.close ()

if __name__ == "__main__":
    main ()
