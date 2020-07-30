# -*- coding: utf-8 -*-
"""
Created on Mon Jan 21 21:19:14 2019

@author: Ramadian Ridho
"""

import numpy as np
import matplotlib.pyplot as plt

def ornsteinUhlenbeck(N):
    t_0 = 0 # define model parameters
    t_end = 1
    length = N
    theta = 1.1
    mu = 0.8
    sigma = 0.3

    t = np.linspace(t_0,t_end,length) # define time axis
    dt = np.mean(np.diff(t))

    y = np.zeros(length)
    y[0] = np.random.normal(loc=0.0,scale=1.0) # initial condition

    drift = lambda y,t: theta*(mu-y) # define drift term, google to learn about lambda
    diffusion = lambda y,t: sigma # define diffusion term
    noise = np.random.normal(loc=0.0,scale=1.0,size=length)*np.sqrt(dt) #define noise process

    # solve SDE
    for i in range(1,length):
     y[i] = y[i-1] + drift(y[i-1],i*dt)*dt + diffusion(y[i-1],i*dt)*noise[i]

    return y


def autocorr(x):
    result = np.correlate(x, x, mode='full')
    #normalize
    result = result / result.max() 
    
    return result[result.size//2:]


#---------------------------------- MAIN ----------------------------------------
N = 2**10

ornstein_process = ornsteinUhlenbeck(N)

plt.figure(0)
plt.title("Ornstein-Uhlenbeck Process")
plt.plot(ornstein_process)

autocorrelation_function = autocorr(ornstein_process)

plt.figure(1)
plt.title("Autocorrelation Function")
plt.plot(autocorrelation_function)


#file = open("data/ornstein_autocorrealtion_function.txt", 'w')
#for i in range(len(autocorrelation_function)):
#    file.write(str(autocorrelation_function[i]) + '\n')
#
#file.close()

del ornstein_process
del autocorrelation_function