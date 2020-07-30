# -*- coding: utf-8 -*-
"""
A script to find factorial of a positive integer value

Created on Mon May 23 16:15:17 2016

@author: Ramadian Ridho
"""

def fact(val):
    """val int ;
       val >= 0"""
    assert val >= 0
    if val == 0:
        return 1
    else:
        return val * fact(val-1)

#==============================================================================
# Main
#==============================================================================
print(fact(6))