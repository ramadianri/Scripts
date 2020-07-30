# -*- coding: utf-8 -*-
"""
Kardar-Parisi-Zhang (KPZ) ver. 1.0

Mensimulasikan Persamaan KPZ dengan melakukan pendekatan menggunakan
metode ETD

Masalah yang diketahui:
    - Gaussian white noise belum diperhitungkan di versi ini
    - Belum terjadi growth, sehingga harus dipaksa dengan cara melakukan
      shift (line 104)
    - Nilai shift masih berdasarkan nilai coba-coba
    - Fluktuasi pada ujung boundary

@author: Ramadian Ridho
"""

import numpy as np
import matplotlib.pyplot as plt



def calculateK_n():
    for i in range(N):
        if i >= 0 and i < N/2:
            n[i] = i
        elif i == N/2:
            n[i] = 0
        else:
            n[i] = -n[ i - int(2*(i - N/2))]
    
    return (n*2*np.pi)/L


#ETD: definisi nilai c 
def ETD_c():
    return -nu * K_n**2


#ETD: definisi fungsi F(h)
def ETD_F(h):
    return -(lamda/2) * (K_n**2) * np.fft.fft(h**2)


def ETD_calculate():    
    #fungsi awal random walk
    def randomWalk(x):
        """x: jumlah step"""
        y = 0
        result = []
        for _ in x:
            result.append(y)
            y += np.random.normal(scale=1)
        return np.array(result)
    
    #https://stackoverflow.com/questions/29050164/produce-random-wavefunction
    def runningMean(x, N):
        """x: jumlah step
           N: window
           Semakin besar nilai window (parameter N), semakin halus random walk"""
        return np.convolve(x, np.ones((N,))/N)[(N-1):]
    
    #ETD: hitung C1 dan C2
    c = ETD_c()
    C1 = np.zeros(len(n))
    C2 = np.zeros(N)
    for i in range(len(n)):
        C1[i] = np.exp(c[i]*deltaT)
        if c[i] == 0:
            C2[i] = 0.0
        else:
            C2[i] = (C1[i] - 1)/(c[i])
    
    #ETD: initial profile
    h = np.zeros((len(t), len(n)), dtype='D')
    hTilde = np.zeros((len(t), len(n)), dtype='D')
    
    h[0] = runningMean(randomWalk(x), 7)
    hTilde[0] = np.fft.fft(h[0])
    
    #ETD: kalkulasi algoritma
    for i in range(len(t)-1):
        hTilde[i+1] = (hTilde[i] * C1) + (ETD_F(h[i]) * C2)
        
        h[i+1] = np.fft.ifft(hTilde[i+1])
    
    #ETD: hasil
    return np.real(h)


#display plot
def displayPlot(data, time):
    """data: input data;
       time: waktu yang diinginkan"""
    assert time < tMax, "Waktu yang dimasukkan melebihi waktu maksimal"
    
    def mapFromTo(val,a,b,c,d):
        """val: input nilai; 
           a,b: input range
           c,d: output range"""
        y=(val-a)/(b-a)*(d-c)+c
        
        return int(y)
    
    timeVal = mapFromTo(time, 0, tMax, 0, len(t))
    shift = 2
    
    plt.plot(x, data[timeVal] + shift*time, label='$t = $' + str(time))
    plt.xlabel('x')
    plt.ylabel('h')
    plt.legend()


#save data to a file
def saveData(data, fileName):
    """data: input data;
       fileName: nama file, string;"""
    with open(fileName, "w") as file:
        for i in range(len(t)):
            for j in range(len(x)):
                file.write(str(data[i,j]) + ',')
            file.write('\n')
    print('Selesai menulis data di ' + fileName)
    file.close()


    
#------------------------ Main ---------------------------------------#
#setup
nu = 0.75
lamda = 0.001
L = 256
N = 512

tMax = 15
deltaT = 0.01

n = np.zeros(N)
K_n = calculateK_n()

#batas x dan t
x = np.linspace(-L, L, N)
t = np.linspace(0, tMax, int(tMax / deltaT))
deltaT = t[1] - t[0]

#kalkulasi ETD
h = ETD_calculate()

#displayPlot
for i in range(14):
    displayPlot(h, i)


#saveData(h, "data/data_ETD.csv")

