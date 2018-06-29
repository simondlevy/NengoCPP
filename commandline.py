#/usr/bin/env python3
'''
Simple Nengo PID control example using command-line i/o

Copyright 2018 Simon D. Levy

MIT License
'''

# Params to play with
Kp = 1.0
Kd = 1.0
sim_time = 0.001
tolerance = 0.01

from nengo_pidcontrol import PIDController

controller = PIDController(Kp, Kd, 0, 1, sim_time) # Ki=0, n_dims = 2

actual = 0

while True:

    target = float(input('Enter a target value (or non-number to quit) > '))

    correction = 0

    while True:
        correction = controller.getCorrection(target, actual)[0]
        actual += correction
        print('Target = %+6.3f    Actual = %+6.3f    Correction = %+6.3f' % (target, actual, correction))
        if abs(target-actual)/abs(target) < tolerance:
            break
