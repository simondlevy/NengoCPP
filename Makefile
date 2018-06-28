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

all: commandline mousetracker

PYVER = 3.6

CFLAGS = -Wall -std=c++11

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
  PYINC = /usr/include/python$(PYVER)
  PYTHON_LIBDIR:=/usr/lib/python$(PYVER)/config-$(PYVER)m-x86_64-linux-gnu/
endif

ifeq ($(UNAME), Darwin)
  PYDIR = /Library/Frameworks/Python.framework/Versions/$(PYVER)
  PYINC = $(PYDIR)/include/python$(PYVER)m
  PYTHON_LIBDIR = $(PYDIR)/lib
endif

OPENCV_COMPILE = `pkg-config --cflags opencv`
OPENCV_LINK = `pkg-config opencv --libs`

mousetracker: mousetracker.o nengo_pidcontrol.o
	g++ -o mousetracker mousetracker.o nengo_pidcontrol.o \
		-L$(PYTHON_LIBDIR) $(OPENCV_LINK) -lpython$(PYVER)

mousetracker.o: mousetracker.cpp nengo_pidcontrol.h
	g++ $(CFLAGS) -c -I $(PYINC) $(OPENCV_COMPILE) mousetracker.cpp 

commandline: commandline.o nengo_pidcontrol.o
	g++ -o commandline commandline.o nengo_pidcontrol.o \
		-L$(PYTHON_LIBDIR) -lpython$(PYVER)

commandline.o: commandline.cpp nengo_pidcontrol.h
	g++ $(CFLAGS) -c -I $(PYINC) commandline.cpp 

nengo_pidcontrol.o: nengo_pidcontrol.cpp nengo_pidcontrol.h
	g++ $(CFLAGS) -c -I $(PYINC) nengo_pidcontrol.cpp 

clean:
	rm -rf mousetracker *.o *~ __pycache__ *.pyc
