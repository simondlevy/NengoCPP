/*
Class header for C++ class for wrapping Nengo PID controller written in Python

Copyright 2018 Simon D. Levy

MIT License
*/

#include <Python.h>
#include "python_class.h"

class NengoPIDController : public PythonClass {

    public:

        NengoPIDController(float Kp, float Kd, float Ki=0, int n_dims=1, float sim_time=0.01,
                int n_neurons=100, float integral_synapse=0.1, float integral_radius=1.0);

        void getCorrection(float target[], float actual[], float correction[]);

    private:

        PyObject * _pInstance;
        PyObject * _pTarget;
        PyObject * _pActual;

        int _n_dims;
};
