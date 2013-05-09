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
    ofile = codecs.open (sys.argv[1] + '.pwar2', 'w',encoding='utf-8')

    prev_syllables = []
    prev_count = 0
    match = []
    tmp = []
    pos = 0

    for k, line in enumerate(( l.strip() for l in ifile)):
        if (k %1000) == 0:
            print k

        syllables = list(ml.ClusterIter(line)) #ml.ClusterIter(line).next ()

        if (len(syllables) < 1): # < 2
            match = []
            prev_syllables = []
            prev_count = 0
            continue

        #ofile.write ("\n\ns=%s p=%s:m=%s\n" %(mystr(syllables), mystr(prev_syllables), mystr(match)))
        if prev_syllables:
            if len(match) > 1 and (len(match)+1) < len(prev_syllables):
                ofile.write ("%s\n" %mystr (prev_syllables[len(match):]))

        if match:
            if startswith (syllables, match):
                prev_count += 1
            else:
                #for u in range (prev_count):
                ofile.write ("%s\n" %mystr (match));
                match = []
                prev_syllables = []
                prev_count = 0

        else:
            match = get_longest_match (syllables, prev_syllables)
            #ofile.write ("==> prev_count= %d match=%s\n" %(prev_count,mystr(syllables)))

            if len(match) < 2:
                #if len(match) == 0:
                #ofile.write ("==> here= t=%s ps=%s\n" %(mystr(tmp),mystr(prev_syllables)))
                if tmp and len(get_longest_match (tmp, prev_syllables)) < 2:
                    if len(prev_syllables) > 2:
                        ofile.seek (pos)
                        ofile.write ("%s\n" %mystr(prev_syllables[1:]))
                tmp = prev_syllables
                match = []
                prev_count = 0
            else:
                if (len(match)+1) < len(prev_syllables):
                    ofile.write ("%s\n" %mystr (prev_syllables[len(match):]))
                prev_count += 1

        pos = ofile.tell ()
        ofile.write ("%s\n" %mystr(syllables))
        prev_syllables = syllables

    ifile.close ()
    ofile.close ()

if __name__ == "__main__":
    main ()
