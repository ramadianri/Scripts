# -*- coding: utf-8 -*-
"""
Create a pattern of a wanderer whom walked randomly. The patern depends on
number of steps that he/she takes. Each step leads either to north, south, east,
or west.

Created on Tue Jun 21 07:16:40 2016

@author: Ramadian Ridho
"""

import random

class Wanderer(object):
    def __init__(self):
        """create a start point in x and y axis"""
        self.xInit = 0
        self.yInit = 0
    
    def move(self, numSteps):
        """numSteps int;
           numSteps >= 0;
           take a steps randomly numSteps times, each to north, south, west, or
           east."""
        assert numSteps >= 0
        
        #create lists that contain each step in x and y axis, start from start point
        self.xPos = [self.xInit]
        self.yPos = [self.yInit]
        
        for i in range(numSteps):
            step = random.choice(['east', 'west', 'north', 'south'])
            if step == 'east':
                self.xInit += 1
                #print ('east: ', self.xInit, self.yInit)
            elif step == 'west':
                self.xInit -= 1
                #print ('west: ', self.xInit, self.yInit)
            elif step == 'north':
                self.yInit += 1
                #print ('north: ', self.xInit, self.yInit)
            elif step == 'south':
                self.yInit -= 1
                #print ('south: ', self.xInit, self.yInit)
            
            self.xPos.append(self.xInit)
            self.yPos.append(self.yInit)
    
    def getX(self):
        """returns a list that contains each position in x axis for every steps"""
        return self.xPos
    
    def getY(self):
        """returns a list that contains each position in y axis for every steps"""
        return self.yPos
            
#==============================================================================
# Main
#==============================================================================
import pylab

mo = Wanderer()
mo.move(5000)

pylab.plot(mo.getX(), mo.getY())