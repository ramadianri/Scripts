# -*- coding: utf-8 -*-
"""
Created on Mon Apr 23 23:27:51 2018

@author: Ramadian Ridho
"""

import numpy as np
import pylab

def slope(x, y):
    """x,y float ;
       return dy/dx"""
    return (5.0*x**2 - y)/(np.exp(x+y))

def euler(x_0, y_0, x_n, numberOfSlices):
    """x_0, y_0, x_n, numberOfSlices float ;
       return array [x[],y[]] """
    x = np.linspace(x_0, x_n, numberOfSlices)
    y = np.zeros(len(x))
    
    y[0] = y_0
    
    deltaX = x[1] - x[0]
    
    for i in range(len(x)-1):
        y[i+1] = y[i] + slope(x[i], y[i]) * deltaX
    
    return np.array([x,y])


x,y = euler(0,1,10,100)

pylab.plot(x,y)