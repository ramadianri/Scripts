# -*- coding: utf-8 -*-
"""
Created on Wed Oct 24 08:08:25 2018

@author: Ramadian Ridho
"""

import numpy as np


def lanzcos(A):
    """A array
       mengembalikan T (matriks tridiagonal) serupa dengan matriks A"""
    n,m = A.shape

    Q = np.empty([n,n])
    
    #nilai awal
    q0 = np.zeros(n)
    r0 = np.random.random(n)
    b0 = np.linalg.norm(r0)
    
    alpha = np.empty(n)
    beta = np.empty(n)
    
    for i in range(n):
        q1 = r0/b0
        a1 = np.dot(np.dot(q1.T,A), q1)
        r1 = np.dot(A,q1) - np.dot(a1,q1) - np.dot(b0,q0)
        b1 = np.linalg.norm(r1)
        
        #isi matriks Q
        Q[:,i] = q1
        
        alpha[i] = a1
        beta[i] = b1
        
        #update
        q0 = q1
        r0 = r1
        b0 = b1
        
#    EYE = np.dot(Q.T,Q)
#    print(EYE)

    #susun matriks T
    T = np.diag(alpha) + np.diag(beta[:-1],1) + np.diag(beta[:-1],-1)
    
    return T