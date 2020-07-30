# -*- coding: utf-8 -*-
"""
Tower of Hanoi
Hindu temple where the puzzle was presented to young priests. At the beginning
of time, the priests were given three poles and a stack of 64 gold disks, each
disk a little smaller than the one beneath it. Their assignment was to transfer
all 64 disks from one of the three poles to another, with two important 
onstraints. They could only move one disk at a time, and they could never place
a larger disk on top of a smaller one.

Created on Mon May 23 16:34:17 2016

@author: Ramadian Ridho
"""

def hanoi(n, s, t, b):
    """n int ; s,t,b string ;
       n = the number of disk(s) ; s = source ; t = target ; b = buffer
       n > 0"""
    assert n > 0
    if n == 1:
        print ('move disk from ', s , ' to ', t)
    else:
        hanoi(n-1, s, b, t)
        hanoi(1, s, t, b)
        hanoi(n-1, b, t, s)

#==============================================================================
# Main
#==============================================================================
hanoi(3, 'A', 'B', 'C')