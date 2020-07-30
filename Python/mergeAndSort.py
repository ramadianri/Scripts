# -*- coding: utf-8 -*-
"""
A script to sort a list. It can be ascending or descending depend on argument 
that we pass which is __lt__ or __gt__

Created on Sat Jun 18 15:35:15 2016

@author: Ramadian Ridho
"""

#def selSort(L):
#    """L list ;
#       sort L in ascending order """
#    for i in range (len(L)-1):
#        minIndex = i
#        minValue = L[i]
#        #j = i + 1
#                
#        #find the lowest value in range L(i+1:)        
#        for j in range((i+1), len(L)):
#            if minValue > L[j]:
#                minIndex = j
#                minValue = L[j]
#        
#        #swap L[i] and L[minIndex]
#        temp = L[i]
#        L[i] = L[minIndex]
#        L[minIndex] = temp
#    
#    return L

def merge(left, right, lt):
    """left, right list ; lt functional argument ;
       returns a new sorted list (ascending by default) from 2 merged lists """
    i = 0
    j = 0
    merged = []
    
    while i < len(left) and j < len(right):
        if lt(left[i], right[j]):
            merged.append(left[i])
            i +=1        
        else:
            merged.append(right[j])
            j += 1
            
    while i < len(left):
        merged.append(left[i])
        i += 1
        
    while j < len(right):
        merged.append(right[j])
        j += 1
    
    return merged

def sort(L, lt = lambda x,y: x < y):
    """L list ; lt functional argument ; 
       returns sorted list from a random list """
    if len(L) < 2:
        return L[:]
    
    else:
        middle = int (len(L)/2)
        left = sort(L[:middle], lt)
        right = sort(L[middle:], lt)
        
        return merge(left, right, lt)

#==============================================================================
# Main
#==============================================================================
L1 = [2, 7, 3, 6, 0, 4, 9, 1]

print (sort(L1, int.__lt__))