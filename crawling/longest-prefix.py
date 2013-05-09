#! /usr/bin/python
# -*- coding: utf-8 -*-

import sys
import codecs
import myanmar.language as ml

def startswith (sd, nd):
    nl = len(nd)
    sl = len(sd)

    if nl > sl:
        return False

    for i in range (nl):
        if sd[i] != nd[i]:
            return False
    return True

def get_longest_match (sd, nd):
    nl = len(nd)
    sl = len(sd)

    if nl > sl:
        nl, sl = sl, nl
        sd, nd = nd, sd

    i = 0
    for i in range (nl):
        if nd[i] != sd[i]:
            break
    else:
        i += 1

    return nd[:i]

def mystr (l):
    return "".join (l)

def main ():
    if len(sys.argv) != 2:
        print "Usage: %s inputFile" %sys.argv[0]
        sys.exit (1)

    ifile = codecs.open (sys.argv[1], 'r', encoding='utf-8')
    ofile = codecs.open (sys.argv[1] + '.prefixes', 'w',encoding='utf-8')

    prev_syllables = []
    prev_count = 0
    match = False

    for line in ( l.strip() for l in ifile):
        syllables = list(ml.ClusterIter(line)) #ml.ClusterIter(line).next ()

        if len(syllables) <= 1:
            match = False
            prev_syllables =  []
            prev_count = 0
            continue

        if match:
            if startswith (syllables, match):
                #print mystr(syllables).encode ('utf-8'), " startswith ", mystr(match).encode ('utf-8')
                prev_count += 1
            else:
                #print mystr(syllables).encode ('utf-8'), " not startswith ", mystr(match).encode ('utf-8')
                if prev_count > 5:
                    ofile.write (mystr(match) + '\n')
                    #else:
                    #print "omitting ", mystr(match).encode ('utf-8')
                prev_syllables = syllables
                prev_count = 0
                match = False
        else:
            match = get_longest_match (syllables, prev_syllables)
            #print "syllable = %s, prev_syl =%s , match = %s" %(mystr (syllables).encode ('utf-8'),\
            #mystr (prev_syllables).encode ('utf-8'),\
            #mystr (match).encode ('utf-8'))
            if len(match) < 2:
                #if prev_syllables:
                #print "omitting ", mystr(prev_syllables).encode ('utf-8')
                #     ofile.write (mystr (prev_syllables) + '\n')
                prev_syllables = syllables
                match = False


    ifile.close ()
    ofile.close ()

if __name__ == "__main__":
    main ()
