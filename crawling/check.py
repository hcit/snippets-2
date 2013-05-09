#! /usr/bin/python
# -*- coding: utf-8 -*-

import re
import sys
import codecs
import myanmar.language as ml

def main ():
    if len(sys.argv) != 3:
        print "Usage: %s syllableFile inputFile" %sys.argv[0]
        sys.exit (1)

    p = re.compile (u'(\u1004\u103a\u1039)?((\u1000\u103b\u1015\u103a|\u100b\u1039\u100b|\u100b\u1039\u100c|\u100d\u1039\u100d|\u100d\u1039\u100e|\u100f\u1039\u100d)|((\u104e\u1004\u103a\u1038|\u1000|\u1001|\u1002|\u1003|\u1004|\u1005|\u1006|\u1007|\u1008|\u1009|\u100a|\u100b|\u100c|\u100d|\u100e|\u100f|\u1010|\u1011|\u1012|\u1013|\u1014|\u1015|\u1016|\u1017|\u1018|\u1019|\u101a|\u101b|\u101c|\u101d|\u101e|\u101f|\u1020|\u1021|\u1023|\u1024|\u1025|\u1026|\u1027|\u1029|\u102a|\u103f|\u1040|\u1041|\u1042|\u1043|\u1044|\u1045|\u1046|\u1047|\u1048|\u1049|\u104a|\u104b|\u104c|\u104d|\u104e|\u104f)(\u1039\u1010\u103d|\u1039\u1000|\u1039\u1001|\u1039\u1002|\u1039\u1003|\u1039\u1005|\u1039\u1006|\u1039\u1007|\u1039\u1008|\u1039\u100b|\u1039\u100c|\u1039\u100d|\u1039\u100e|\u1039\u100f|\u1039\u1010|\u1039\u1011|\u1039\u1012|\u1039\u1013|\u1039\u1014|\u1039\u1015|\u1039\u1016|\u1039\u1017|\u1039\u1018|\u1039\u1019|\u1039\u101a|\u1039\u101b|\u1039\u101c|\u1039\u101e|\u1039\u1021)?))(\u103a)?(\u103b)?(\u103c)?(\u103d)?(\u103e)?(\u1031)?(\u102d|\u102e)?(\u102f|\u1030)?(\u1032|\u1036)?(\u102b|\u102c)?(\u1037)?(\u103a)?(\u1037)?(\u1038)?', re.U)

    sfile = codecs.open (sys.argv[1], 'r', encoding='utf-8')
    ifile = codecs.open (sys.argv[2], 'r', encoding='utf-8')
    ofile = codecs.open (sys.argv[2] + '.checked', 'w',encoding='utf-8')

    for line in (l.strip() for l in ifile):
        for i in ml.ClusterIter (line):
            if not p.search (i):
                ofile.write (i + '\t' + line + '\n')
                break


    sfile.close ()
    ifile.close ()
    ofile.close ()

if __name__ == "__main__":
    main ()
