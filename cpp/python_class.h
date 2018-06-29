/*
Generic class header for C++ class for wrapping Python classes in C++

Copyright 2018 Simon D. Levy

MIT License
*/

#include <Python.h>

class PythonClass {

    protected:

        PythonClass(const char * moduleName, const char * className);

        PyObject * _pClass;
        PyObject * _pInstance;
};
