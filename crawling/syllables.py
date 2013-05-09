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
    ofile = codecs.open (sys.argv[1] + '.syllables', 'w',encoding='utf-8')

    prev_syllables = u""
    prev_count = 0

    for line in ( l.strip() for l in ifile):
        syllables = list(ml.ClusterIter(line)) #ml.ClusterIter(line).next ()

        if len(syllables) < 2:
            syllables = "".join (syllables)
        else:
            syllables = "".join (syllables[:2])
            if u"\u1039" in syllables or u'\u103F' in syllables:
                continue

        if syllables == prev_syllables:
            prev_count += 1
        else:
            #if (u"\u1039" in prev_syllables and prev_count > 25) or (prev_count > 50):
            if (prev_count > 50):
               ofile.write ('%s\n' %(prev_syllables))
               #else:
               #print "skipping ", prev_syllables.encode ('utf8')
            prev_count = 0
            prev_syllables = syllables

    ifile.close ()
    ofile.close ()

if __name__ == "__main__":
    main ()
