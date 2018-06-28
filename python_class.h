/*
Generic class header for C++ class for wrapping Python classes in C++

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

class PythonClass {

    protected:

        PythonClass(const char * moduleName, const char * className);

        PyObject * _pClass;
        PyObject * _pInstance;
};
