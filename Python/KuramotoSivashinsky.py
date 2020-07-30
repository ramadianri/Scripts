# -*- coding: utf-8 -*-
"""
Created on Tue Aug 14 06:52:44 2018

@author: Ramadian Ridho
"""

import numpy as np
import matplotlib.pyplot as plt
import csv

def calculateK_n():
    for i in range(N):
        if i >= 0 and i < N/2:
            n[i] = i
        elif i == N/2:
            n[i] = 0
        else:
            n[i] = -n[ i - int(2*(i - N/2))]
    
    return (n*2*np.pi)/L
    
#ETD: hitung c
def ETD_c():
    return K_n**2 - K_n**4


#ETD: hitung F(u)
def ETD_F(u):
    return -0.5j * K_n * np.fft.fft(u**2)


def ETD_calculate():    
    #fungsi awal
    def u(x,t):
        amplitudo = 0.5
        omega = np.pi*0.1
        k = 1
    
        return amplitudo * np.sin(omega*t + k*x)
    
    #ETD hitung C dan C1
    c = ETD_c()
    C = np.zeros(len(n))
    C1 = np.zeros(N)
    for i in range(len(n)):
        C[i] = np.exp(c[i]*deltaT)
    
        if c[i] == 0:
            C1[i] = 0.0
        else:
            C1[i] = (C[i] - 1)/(c[i])
    
    
    #ETD: syarat awal
    u_0 = u(x,0)
    
    u = np.zeros((len(t), len(n)), dtype='D')
    uTilde = np.zeros((len(t), len(n)), dtype='D')
    
    u[0] = u_0
    uTilde[0] = np.fft.fft(u[0])
    
    #ETD: kalkulasi algoritma
    for i in range(len(t)-1):
        uTilde[i+1] = (uTilde[i] * C) + (ETD_F(np.real(u[i])) * C1)
            
        u[i+1] = np.fft.ifft(uTilde[i+1])
    
    #ETD: hasil
    return np.real(u)


#display plot
def displayPlot(data, time):
    assert time < tMax, "Waktu yang dimasukkan melebihi waktu maksimal"
    def mapFromTo(x,a,b,c,d):
        """x: input value; 
           a,b: input range
           c,d: output range"""
        y=(x-a)/(b-a)*(d-c)+c
        return int(y)
    
    timeVal = mapFromTo(time, 0, tMax, 0, len(t))
    
    plt.plot(x, data[timeVal], 'b')


def saveData(u, fileName):
    with open(fileName, "w") as file:
        for i in range(len(t)):
            for j in range(len(x)):
                file.write(str(u[i,j]) + ',')
            file.write('\n')
    print('Selesai menulis data di ' + fileName)
    file.close()

#----------------------- MAIN -------------------------------#
#setup
L = 256
N = 512
tMax = 100
deltaT = 0.1

n = np.zeros(N)
K_n = calculateK_n()

#batas x dan t
x = np.linspace(-L, L, N)
t = np.linspace(0, tMax, int(tMax / deltaT))
deltaT = t[1] - t[0]


u = ETD_calculate()

displayPlot(u, 50)
#saveData(u, "data/data_ETD.csv")
