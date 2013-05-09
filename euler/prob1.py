#! /usr/bin/env python
num = 0     #Starting Number
sum = 0
def prob1(maxNum):
    global num,sum
    while num < maxNum:
        if ( num % 3 == 0) or (num % 5 ==0):
            sum = sum +num
        num = num + 1
    return sum


sum([x for x in range(1000) if x % 3== 0 or x % 5== 0])    