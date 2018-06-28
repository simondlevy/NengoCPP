/*
Generic C++ class for wrapping Python classes

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

#include "python_class.h"

PythonClass::PythonClass(const char * moduleName, const char * className)
{
    // Initialize Python access
    Py_Initialize();

    // Make sure we can access Python modules in the current directory
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(\".\")");

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

    // Ensure class is callable
    if (!PyCallable_Check(pClass)) {
        fprintf(stderr, "%s is not a callable class\n", className);
        exit(1);
    }
}
