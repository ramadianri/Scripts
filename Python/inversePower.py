# -*- coding: utf-8 -*-
"""
Created on Wed Oct 24 08:56:03 2018

@author: Ramadian Ridho
"""

import numpy as np

def gaussElimTrid(A, y):
    n = len(y)
    A_elim = np.copy(A)
    y_elim = np.copy(y)
    for i in range(1, n):
        multiplierFactor = A[i][i-1] / A_elim[i-1][i-1]
        for j in range(i-1, n):
            A_elim[i][j] = A_elim[i][j] - multiplierFactor * A_elim[i-1][j]
    
        y_elim[i] = y_elim[i] - multiplierFactor * y_elim[i-1]    
    
    x = np.zeros(n)
    for i in reversed(range(n)):
        if i == n-1:
            x[i] = y_elim[i] / A_elim[i][i]
        else:
            x[i] = (y_elim[i] - A_elim[i][i+1]*x[i+1]) / A_elim[i][i]
    
    return x


def inversePower(A, epsilon):
    m,n = A.shape
    x0 = np.ones(n)
    c0 = 0
    
    A = A - (np.eye(n)*epsilon)
    for i in range(1000):
        y0 = gaussElimTrid(A,x0)

        c1 = (np.dot(y0.T,x0)) / (np.dot(x0.T,x0))
        
        x1 = y0 / np.linalg.norm(y0)
        
        if np.abs(c1-c0) < 0.000001:
            break
        
        x0 = x1
        c0 = c1
    
    lambda1 = (1/c1) + epsilon
    
    return lambda1, x1