#! /usr/bin/python
from __future__ import with_statement
from math import *
import sys
import os

__author__  ="thurahaling06@gmail.com"
__date__    ="$Feb 23, 2009 7:20:18 PM$"


NOT_EXPR = '\''
AND_EXPR = ''
OR_EXPR  = '|'

charlist = [chr(i) for i in range(97,123)]     # return a list from a to z

def getVarNum(truth_values):
    """Take truth values of a boolean function in string format  and \
    return the number of variables required to describe it in DNF."""
    length = len(truth_values)
    return int(ceil(log10(length) / log10(2)))

def getFuncRepr(truth_values):
    """Take the truth values of a boolean function in string format  and \
    return the string representation of the function."""
    count = getVarNum(str(truth_values))
    functionStr = "f("
    for i in range(0, count):
        if i == (count -1):
            functionStr = functionStr + charlist[i]
        else:
            functionStr = functionStr + charlist[i] + ","
    functionStr = functionStr + ")"
    return functionStr

def getTruthTable(truth_values):
    """Take the truth values of a boolean function in string format  and \
    return the truth table for that function in a list."""
    # We will return the truth table in dictionary format , for example,
    # [[(0, 0, 0), 0], [(0, 0, 1), 1], [(0, 1, 0), 0], [(0, 1, 1), 0], [(1, 0, 0), 1], [(1, 0, 1), 0], [(1, 1, 0), 1], [(1, 1, 1), 1]]
    # Since we don't know the exact number of variables for the function, we will first write the python expression to  a str
    # Then, evaluate it using eval ...
    # Is there any smarter way of doing this in python ?

    # First, get the require variable numbers and store them in a list
    var_list = []
    count = getVarNum(truth_values)
    for m in range(0, count):
        var_list.append(charlist[m])

    # Ok, start writing the expression
    truth_table_expr = '[[('
    for x in var_list:
        truth_table_expr += x + ','
    truth_table_expr += ')] '
    # Now, the expression is [[(a,b, ...)]

    for x in var_list:
        truth_table_expr += ' for ' + x + ' in range(0,2)'
    truth_table_expr += (']')

    # truth_table = [[(a,b, ... )]  for a in range(0,2) for b in range(0,2) ...]
    truth_table = eval(truth_table_expr)

    #Add truth values
    n = 0
    for val in str(truth_values):
        truth_table[n].append(val)
        n += 1

    return truth_table

def printTruthTable(truth_values,output='Q'):
    """Takethe truth values of a boolean function in string  format  and \
    print the truth table for that function."""
    count = getVarNum(truth_values)
    truth_table = getTruthTable(truth_values)
    global charlist

    for i in range(0,count):
        print charlist[i],'\t ',
    print output
    print "-" * ( 8 * ( count + 1 ) )
    for val in truth_table:
        for i in range(0, count):
            print val[0][i], '\t','|',
        print val[1],'\t','|'

def getDNF(truth_values):
    """Takethe truth values of a boolean function in string format  and \
    return the string representation of DNF (Disjunctive Normal Form) value of that function."""
    DNF = ""
    count = getVarNum(truth_values)
    truth_table = getTruthTable(truth_values)
    global charlist, AND_EXPR, OR_EXPR, NOT_EXPR

    for val in truth_table:
        if int(val[1]):
            for i in range(0,count):
                if val[0][i]:
                    DNF += charlist[i]
                else:
                    DNF += charlist[i] + NOT_EXPR
                DNF += AND_EXPR
                i += 1
            DNF += OR_EXPR
    DNF = DNF.rstrip(OR_EXPR + AND_EXPR + NOT_EXPR + ' ') #strip unnecessary operators on the right side
    return DNF

if __name__ == "__main__":

    truth_values = '01001011010010110100101101001011'
    printTruthTable(truth_values)
    print "The DNF value is for the function ", getFuncRepr(truth_values)," is ", getDNF(truth_values),'.'
