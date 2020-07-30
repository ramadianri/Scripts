# -*- coding: utf-8 -*-
"""
Created on Tue Apr 24 08:29:20 2017

@author: Ramadian Ridho
"""

import numpy as np
import matplotlib.pyplot as plt


def slopeY(v):
    return v

def F_etd(t,y):
    A = 1.2
    w = np.pi*0.1
    return -np.sin(y) + A*np.sin(w*t)

def ETD(t_0, t_n, y_0, v_0, c, numberOfSlices):
    """t_0, y_0, t_n, numberOfSlices float ;
       return array [t[],y[],v[]] """
    t = np.linspace(t_0, t_n, numberOfSlices)
    y = np.zeros(len(t))
    v = np.zeros(len(t))
    
    y[0] = y_0
    v[0] = v_0
    
    deltaT = t[1] - t[0]
    
    for i in range(len(t)-1):
        y[i+1] = y[i] + slopeY(v[i]) * deltaT
        v[i+1] = v[i] * np.exp(c*deltaT) + F_etd(t[i], y[i]) * (np.exp(c*deltaT)-1) / c
    
    return np.array([t,y,v])


g = 0.2

t_0 = 0
t_n = 100
y_0 = 0
v_0 = 0
c = -g
numberOfSlices = 10*t_n

t, y, v = ETD(t_0, t_n, y_0, v_0, c, numberOfSlices)

plt.plot(t, y, 'r--')