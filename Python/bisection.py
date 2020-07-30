# -*- coding: utf-8 -*-
"""
Bisection, a script to find nth root of a value

Created on Thu May 19 13:25:26 2016

@author: Ramadian Ridho
"""

def withinEpsilon(x, y, epsilon):
    """x, y, epsilon float ; 
       epsilon > 0.0 ;
       returns True if x is within epsilon y """
    return abs(x - y) <= epsilon

def isEven(x):
    """x int ;
       returns True if x is even"""
    return x % 2 == 0

def findRoot(pwr, val, epsilon):
    """pwr int ; val, epsilon float ;
       pwr and epsilon > 0 ;
       returns a value withinEpsilon of val**pwr"""
    
    assert pwr > 0 and epsilon > 0
    
    if isEven(pwr) and val < 0:
        return print('Error: If power is even, then value must be positive')
    
    low = -abs(val)
    high = max(abs(val), 1.0)
    ans = (low + high) / 2.0
    
    while not withinEpsilon(ans**pwr, val, epsilon):
        if ans**pwr < val:
            low = ans
        else:
            high = ans
        ans = (low + high) / 2.0
    
    return ans
#==============================================================================
# Main
#==============================================================================
power = 4
value = 16.0
epsilon = 0.001

ans = findRoot(power, value, epsilon)

print (ans)