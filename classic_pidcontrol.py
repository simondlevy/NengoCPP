'''
Generic PID control in Python

Copyright 2018 Simon D. Levy

This file is part of HackflightNengo.

HackflightNengo is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as 
published by the Free Software Foundation, either version 3 of the 
License, or (at your option) any later version.
This code is distributed in the hope that it will be useful,     
but WITHOUT ANY WARRANTY without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License 
along with this code.  If not, see <http:#www.gnu.org/licenses/>.
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
