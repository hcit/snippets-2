#! /usr/bin/python
# -*- coding: utf-8 -*-

import sys
import codecs
import myanmar.language as ml
import nltk
import nltk.tokenize
from nltk.collocations import *
import os.path
import cPickle

def progress (i):
    if i % 5000 == 0:
        print "%d" %i

def main ():
    if len(sys.argv) != 2:
        print "Usage: %s inputFile" %sys.argv[0]
        sys.exit (1)

    if (os.path.exists (sys.argv[1] + '.tpkl')):
        print "Found pickle."
        with open(sys.argv[1] + '.tpkl', 'rb') as fil:
            finder3 = cPickle.load (fil)
    else:
        ifile = codecs.open (sys.argv[1], 'r', encoding='utf-8')

        syllables = []
        skip = "per()".join (ml.puncts + ml.digits)
        for i, line in enumerate( l.strip() for l in ifile):
            progress (i)
            line = line.replace (" ", "")
            for p in skip:
                line = line.replace (p, "")
            try:
                for c in ml.ClusterIter(line):
                    syllables += [c]
            except Exception, e:
                print str(e), line, c

        ifile.close ()

        finder3 = TrigramCollocationFinder.from_words(syllables)
        finder3.apply_freq_filter(10) # only trigrams that appear 10+ times

        # remove stopwords
        stopwords = []
        with codecs.open ('stopwords', 'r', 'utf8') as stopwordFile:
            for each in stopwordFile:
                stopwords.append (each.strip())
        def contains_stopwords (*syllables):
            for each in stopwords:
                if each in syllables:
                    return True
            return False
        finder3.apply_ngram_filter(contains_stopwords)

        with open(sys.argv[1] + '.tpkl', 'wb') as fil:
            cPickle.dump (finder3, fil)

    COUNT = 1500
    skip = ['likelihood_ratio',]
    trigram_measures = nltk.collocations.TrigramAssocMeasures()
    measures =[x for x in dir (trigram_measures) if x[0] != '_' and x not in skip]

    with codecs.open (sys.argv[1] + '.trigrams', 'w', 'utf8' ) as ofile:
        for each in measures:
            print each
            for trigrams in finder3.nbest( getattr(trigram_measures, each), COUNT):
                ofile.write ("".join (trigrams) + '\n')

if __name__ == "__main__":
    main ()
