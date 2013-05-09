#! /usr/bin/python
# -*- coding: utf-8 -*-

import sys
import codecs
import myanmar.language as ml
import nltk
import itertools

def mystr (l):
    return "".join (l)

def _bigrams(p):
    return [p[:1]] + [p[i:][:2] for i in range (1, len(p), 2)] +  [p[i:][:2] for i in range (0, len(p), 2)]

def main ():
    if len(sys.argv) != 2:
        print "Usage: %s inputFile" %sys.argv[0]
        sys.exit (1)

    ifile = codecs.open (sys.argv[1], 'r', encoding='utf-8')

    for k, line in enumerate(( l.strip() for l in ifile)):
        print line.encode ('utf8')
        syllables = list(ml.ClusterIter(line))
        bigrams     = nltk.bigrams (syllables)
        trigrams    = nltk.trigrams (syllables)
        tetragrams  = nltk.bigrams (["".join (x) for x in _bigrams(syllables)]) if len (syllables) > 3 else []
        for each in itertools.chain (bigrams, trigrams, tetragrams):
            print "".join(each).encode ('utf8')
    ifile.close ()

if __name__ == "__main__":
    main ()
