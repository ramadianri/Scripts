# -*- coding: utf-8 -*-
"""
Created on Tue Apr 24 02:11:06 2018

@author: Ramadian Ridho
"""

def function(x):
    return x**2 - 4

def functionDerivative(x):
    return 2*x

def lessThanEpsilon(deltaX, epsilon):
    """deltaX, epsilon float ; 
       epsilon > 0.0 ;
       returns True if delta x less than epsilon """
    return abs(deltaX) < epsilon

def bisection(lowGuess, highGuess, epsilon):
    """lowGuess, highGuess int ; epsilon float
       return aprroximation of root """
    assert function(lowGuess) * function(highGuess) < 0 , 'Kedua nilai tebakan tidak berada diantara nilai akar fungsi, silahkan ganti nilai tebakan'

    while not lessThanEpsilon(highGuess-lowGuess, epsilon):
        approx = (lowGuess + highGuess) / 2.0
        
        if function(lowGuess) * function(approx) == 0:
            return approx
        elif function(lowGuess) * function(approx) < 0:
            highGuess = approx
        else:
            lowGuess = approx
    
    return approx

def newtonRaphson(x_0, epsilon):
    """x_0, epsilon float
       return aprroximation of root """
    assert functionDerivative(x_0) != 0, 'y’(x) harus bernilai tidak sama dengan 0'

    x_1 = x_0 - (function(x_0) / functionDerivative(x_0))
    
    while not lessThanEpsilon(x_1-x_0, epsilon):
        x_0 = x_1
        x_1 = x_0 - (function(x_0) / functionDerivative(x_0))
    
    return x_1

def secant(x_0, x_1, epsilon):
    """x_0, x_1, epsilon float
       return aprroximation of root """
    assert function(x_1) - function(x_0) != 0 , 'nilai tebakan tidak boleh menyebabkan function(x 1) − function(x 0) bernilai 0'

    x_2 = x_1 - function(x_1) * ((x_1 - x_0)/(function(x_1) - function(x_0)))
    
    while not lessThanEpsilon(x_2-x_1, epsilon):
        x_0 = x_1
        x_1 = x_2
        x_2 = x_1 - function(x_1) * ((x_1 - x_0)/(function(x_1) - function(x_0)))
        
    return x_2


approxBisection = bisection(0, 5, 0.0001)
approxNR = newtonRaphson(5, 0.0001)
approxSecant = secant(0, 5, 0.0001)