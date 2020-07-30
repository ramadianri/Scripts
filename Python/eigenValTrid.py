# -*- coding: utf-8 -*-
"""
Find all eigen values from a tridiagonal matrix

Created on Thu Apr 26 21:28:09 2018

@author: Ramadian Ridho
"""

import numpy as np
from numpy import linalg as la


def isPositive(value):
    """Returns true if value is positive, false otherwise.""" 
    return value >= 0


def Polynom(A, lamda):
    """A array ; lamda float
       return characteristic polynomial and number of agreements of sign between
       consecutive members of the sign sequence for given lambda"""
    P = np.ones(len(A)+1)   #P[0] = 1
    P[1] = A[0][0] - lamda
    
    sumSameSignSeq = 0.
    
    for i in range(1,len(A)+1):
        if i >= 2:
            P[i] = (A[i-1][i-1] - lamda) * P[i-1] - A[i-2][i-1] * A[i-1][i-2] * P[i-2]
        
        if isPositive(P[i-1]) == isPositive(P[i]):
            sumSameSignSeq += 1
       
    return P, sumSameSignSeq


def boundary(A):
    """A array
       return the biggest sum from each row, to be used as boundary for searching
       all eigen values"""
    sumRows = np.empty(len(A))
    for i in range(len(A)):
        sumRow = 0
        for j in range(len(A)):
            sumRow += A[i][j]
        
        sumRows[i] = sumRow
    
    rightBoundary = max(sumRows)
    leftBoundary = -rightBoundary
    
    return np.array([leftBoundary, rightBoundary])


def separateRoots(A, edge):
    """A, edge array
       return local boundary to separate the roots into disjoint subintervals"""
    localBoundary = []
    edgeTemp = []
    
    low, high = edge
    
    while len(edgeTemp) >= 0:
        lamdaApprox = (low + high) / 2.0
        
        s_low = Polynom(A,low)[1]
        s_high = Polynom(A,high)[1]
        s_approx = Polynom(A,lamdaApprox)[1]
    
        left = s_low - s_approx
        right = s_approx - s_high
    
        if left == 1:
            localBoundary.append([low,lamdaApprox])
            
        elif left != 1 and left != 0:
            highLeft = lamdaApprox
            lowLeft = low
            edgeTemp.append([lowLeft,highLeft])
            
        if right == 1:
            localBoundary.append([lamdaApprox,high])
        
        elif right != 1 and right != 0:
            lowRight = lamdaApprox
            highRight = high
            edgeTemp.append([lowRight,highRight])
        
        if len(edgeTemp) == 0:
            break
        else:
            low, high = edgeTemp[0]
            edgeTemp.remove(edgeTemp[0])
    
    return localBoundary


def bisection(A, localBoundary, epsilon):
    """A, localBoundary array ; epsilon float
       return aprroximation of roots """
    lamdaApprox = np.empty(len(localBoundary))
    
    for i in range(len(localBoundary)):
        lowGuess = localBoundary[i][0]
        highGuess = localBoundary[i][1]

        while not abs(highGuess-lowGuess) < epsilon:
            approx = (lowGuess + highGuess) / 2.0
            
            if Polynom(A,lowGuess)[0][len(A)] * Polynom(A,approx)[0][len(A)] == 0:
                lamdaApprox[i] = approx
            elif Polynom(A,lowGuess)[0][len(A)] * Polynom(A,approx)[0][len(A)] < 0:
                highGuess = approx
            else:
                lowGuess = approx
        
        lamdaApprox[i] = approx
    
    return lamdaApprox


def eigenValueTrid(A):
    """A array
       return all eigen values from a tridiagonal matrix"""
    #find the value at the end of the boundary
    edge = boundary(A)
    
    #separate the roots into disjoint subintervals
    localBoundary = separateRoots(A, edge)
    
    #use bisection method to find roots of P_n(lamda)
    eigenVal = bisection(A, localBoundary, 0.0001)
    
    return eigenVal


M = np.diag([2,5,4,3,5]) + np.diag([1,2,2,1],1) + np.diag([1,2,2,1],-1)
#M = np.diag([2,2,2,2,2,2]) + np.diag([1,1,1,1,1],1) + np.diag([1,1,1,1,1],-1)

eigenVal = eigenValueTrid(M)
print (eigenVal)
eigenValNumpy, eigenVecNumpy = la.eig(M)   #as a comparison
print (eigenValNumpy)
