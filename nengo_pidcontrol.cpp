/*
C++ class for wrapping Nengo PID controller written in Python

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

#include "nengo_pidcontrol.h"

NengoPIDController::NengoPIDController(float Kp, float Kd, float Ki, int n_dims, float sim_time,
                int n_neurons, float integral_synapse, float integral_radius)
{
    const char * moduleName = "nengo_pidcontrol";
    const char * className  = "PIDController";

    // Initialize Python access
    Py_Initialize();

    // Build the name object
    PyObject * pName = PyUnicode_FromString(moduleName);

    // Load the module object
    PyObject * pModule = PyImport_Import(pName);
    if (pModule == NULL) {
        fprintf(stderr, "Error loading module %s\n", moduleName);
        exit(1);
    }

    // pDict is a borrowed reference 
    PyObject * pDict = PyModule_GetDict(pModule);

    // Build the name of a callable class 
    PyObject * pClass = PyDict_GetItemString(pDict, className);

    // Create an instance of the class
    _pInstance = NULL;
    if (PyCallable_Check(pClass)) {

        //setup args for constructor
        PyObject * pArgs = PyTuple_New(8);
        PyTuple_SetItem(pArgs, 0, PyFloat_FromDouble(Kp));
        PyTuple_SetItem(pArgs, 1, PyFloat_FromDouble(Kd));
        PyTuple_SetItem(pArgs, 2, PyFloat_FromDouble(Kd));
        PyTuple_SetItem(pArgs, 3, PyLong_FromLong(n_dims));
        PyTuple_SetItem(pArgs, 4, PyFloat_FromDouble(sim_time));
        PyTuple_SetItem(pArgs, 5, PyLong_FromLong(n_neurons));
        PyTuple_SetItem(pArgs, 6, PyFloat_FromDouble(integral_synapse));
        PyTuple_SetItem(pArgs, 7, PyFloat_FromDouble(integral_radius));

        _pInstance = PyObject_CallObject(pClass, pArgs); 
    }
    else {
        fprintf(stderr, "%s is not a callable class\n", className);
        exit(1);
    }

    // Create tuples to hold target, actual
    _pTarget =  PyTuple_New(n_dims);
    _pActual =  PyTuple_New(n_dims);

    // Store input params for getCorrection()
    _n_dims = n_dims;
}

void NengoPIDController::getCorrection(float target[], float actual[], float correction[])
{
    for (int k=0; k<_n_dims; ++k) {
        PyTuple_SetItem(_pTarget, k, PyFloat_FromDouble(target[k]));    
        PyTuple_SetItem(_pActual, k, PyFloat_FromDouble(actual[k]));    
    }

    PyObject * pCorrection = PyObject_CallMethod(_pInstance, "getCorrection", "(OO)", _pTarget, _pActual);

    for (int k=0; k<_n_dims; ++k) {
        correction[k] = PyFloat_AsDouble(PyTuple_GetItem(pCorrection, k));
    }
}
