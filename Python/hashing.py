# -*- coding: utf-8 -*-
"""
Created on Sun Jun 19 15:03:22 2016

@author: Ramadian Ridho
"""

class intSet(object):
    #intSet is a set of integers
    def __init__(self):
        """create an empty set of integers """
        self.numSlot = 11
        self.value = []
        for i in range (self.numSlot):
            self.value.append([])
            
    def hashE(self, e):
        #private function, should not be used outside of class
        return abs(e) % len(self.value)
        
    def insert(self, e):
        """insert e into self """
#        for i in self.value[self.hashE(e)]:
#            if i == e:
#                return
        self.value[self.hashE(e)].append(e)
        
    def member(self, e):
        """returns True if e is in self, otherwise returns False """
        return e in self.value[self.hashE(e)]
    
    def __str__(self):
        """returns a string representation of self """
        element = []
        for slot in self.value:
            for e in slot:
                element.append(e)
        element.sort
        
        result = ''
        for e in element:
            result = result + str(e) + ', '
        
        return '(' + result[:-2] + ')'
        
#==============================================================================
# Main
#==============================================================================
foo = intSet()
foo.insert(5)
foo.insert(7)
print (foo)
print (foo.member(3))
