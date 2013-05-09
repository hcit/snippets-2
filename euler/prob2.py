#! /usr/bin/env python

x = 1
y = 2
def prob2(maxNum):
    sum = 0
    global x,y
    while y<maxNum:
        if not y%2:
            sum = sum + y
        y = x + y
        x = y - x
    return sum

print prob2(4000000)