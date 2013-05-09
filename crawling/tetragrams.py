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

def possible_bigram_list (p):
    lst = [p[:1]] + [p[i:][:2] for i in range (1, len(p), 2)] +  [p[i:][:2] for i in range (0, len(p), 2)]
    return [x for x in lst if len(x) > 1]


def main ():
    if len(sys.argv) != 2:
        print "Usage: %s inputFile" %sys.argv[0]
        sys.exit (1)

    if (os.path.exists (sys.argv[1] + '.dpkl')):
        print "Found pickle."
        with open(sys.argv[1] + '.dpkl', 'rb') as fil:
            finder4 = cPickle.load (fil)
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
                p = [c for c in ml.ClusterIter(line)]
                for each in possible_bigram_list (p):
                    syllables += ["".join (each)]
            except Exception, e:
                print str(e), line, c
        ifile.close ()

        finder4 = BigramCollocationFinder.from_words (syllables)
        finder4.apply_freq_filter(10) # only bigrams that appear 3+ times

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
        finder4.apply_ngram_filter(contains_stopwords)

        with open(sys.argv[1] + '.dpkl', 'wb') as fil:
            cPickle.dump (finder4, fil)

    COUNT = 1500
    skip = ['likelihood_ratio',]
    bigram_measures = nltk.collocations.BigramAssocMeasures()
    measures =[x for x in dir (bigram_measures) if x[0] != '_' and x not in skip]

    with codecs.open (sys.argv[1] + '.tetragrams', 'w', 'utf8' ) as ofile:
        for each in measures:
            print each
            for bigrams in finder4.nbest(getattr(bigram_measures, each), COUNT):
                ofile.write ("".join (bigrams) + '\n')

if __name__ == "__main__":
    main ()
