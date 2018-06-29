'''
Generic PID control in Python

Copyright 2018 Simon D. Levy

MIT License
'''

import numpy as np

class PIDController(object):

    def __init__(self, Kp, Kd, Ki=0, n_dims=1):

        self.Kp = Kp
        self.Kd = Kd
        self.Ki = Ki

        self.err_prev = np.zeros(n_dims)
        self.err_sum = np.zeros(n_dims)

        self.correction = 0
    
    def getCorrection(self, target, actual):

        # Make inputs into arrays if they aren't already
        target = np.array(target)
        actual = np.array(actual)

        err = target - actual
        self.correction = self.Kp*err + self.Ki*(self.err_sum) + self.Kd*(err-self.err_prev) 

        self.err_prev = err
        self.err_sum += err

        # Return correction as tuple
        return tuple(self.correction)
