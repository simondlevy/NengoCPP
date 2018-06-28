/*
Class header for C++ class for wrapping Nengo PID controller written in Python

Copyright 2018 Simon D. Levy

This file is part of NengoCPlusPlus.

NengoCPlusPlus is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as 
published by the Free Software Foundation, either version 3 of the 
License, or (at your option) any later version.
This code is distributed in the hope that it will be useful,     
but WITHOUT ANY WARRANTY without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License 
along with this code.  If not, see <http:#www.gnu.org/licenses/>.
*/

#include <Python.h>

class NengoPIDController {

    public:

        NengoPIDController(float Kp, float Kd, float Ki=0, int n_dims=1, float sim_time=0.01,
                int n_neurons=100, float integral_synapse=0.1, float integral_radius=1.0);

        void getCorrection(float target[], float actual[], float correction[]);

    private:

        PyObject * _pInstance;
        PyObject * _pTarget;
        PyObject * _pActual;

        int _n_dims;
        float _sim_time;
};
