# Makefile for C++ mouse-tracker example
#
#Copyright 2018 Simon D. Levy
#
#This file is part of NengoCPlusPlus.
#
#NengoCPlusPlus is free software: you can redistribute it and/or modify
#it under the terms of the GNU Lesser General Public License as 
#published by the Free Software Foundation, either version 3 of the 
#License, or (at your option) any later version.
#This code is distributed in the hope that it will be useful,     
#but WITHOUT ANY WARRANTY without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU Lesser General Public License 
#along with this code.  If not, see <http:#www.gnu.org/licenses/>.

all: mousetracker

CFLAGS = -Wall -std=c++11

# Linux
#PYINC = /usr/include/python3.5m
#PYTHON_LIBDIR:=$(shell python -c 'from distutils import sysconfig; print sysconfig.get_config_var("LIBDIR")')

# Mac OS
PYDIR = /Library/Frameworks/Python.framework/Versions/3.6
PYINC = $(PYDIR)/include/python3.6m
PYTHON_LIBDIR = $(PYDIR)/lib

OPENCV_COMPILE = `pkg-config --cflags opencv`
OPENCV_LINK = `pkg-config opencv --libs`

mousetracker: mousetracker.o nengo_pidcontrol.o
	g++ -o mousetracker mousetracker.o nengo_pidcontrol.o \
		-L$(PYTHON_LIBDIR) $(OPENCV_LINK) -lpython3.6m

mousetracker.o: mousetracker.cpp nengo_pidcontrol.h
	g++ $(CFLAGS) -c -I $(PYINC) $(OPENCV_COMPILE) mousetracker.cpp 

nengo_pidcontrol.o: nengo_pidcontrol.cpp nengo_pidcontrol.h
	g++ $(CFLAGS) -c -I $(PYINC) nengo_pidcontrol.cpp 

run: mousetracker
	./mousetracker

mouse: mousetracker
	./mousetracker

clean:
	rm -rf mousetracker *.o *~ __pycache__ *.pyc
