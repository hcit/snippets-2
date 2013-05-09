#! /usr/bin/python
# -*- coding: utf-8 -*-
import sys
import codecs
import myanmar.language

def subseqs (seq, length):
    def _subseqs_ (_seq):
        if len(_seq) <= length:
            return [_seq]
        return [_seq] + _subseqs_ (_seq[:-1])

    if len(seq) <= length:
        return [seq]
    return _subseqs_ (seq) + subseqs (seq[1:], length)

def main ():
    if len(sys.argv) != 2:
        print "Usage: %s inputFile" %sys.argv[0]
        sys.exit (1)

    ifile = codecs.open (sys.argv[1], 'r', encoding='utf8')
    ofile = codecs.open (sys.argv[1] + '.pwar', 'w',encoding='utf8')

    for line in ifile.readlines ():
        line = line.strip ()
        out  = u""
        clusters = [c for c in myanmar.language.ClusterIter(line)]
        seqs = subseqs (clusters, 2)
        for s in seqs:
            out += u"".join (s) + '\n'
        ofile.write (out)

    ifile.close ()
    ofile.close ()

if __name__ == "__main__":
    main ()
