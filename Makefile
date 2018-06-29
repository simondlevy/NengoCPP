# Makefile for C++ mouse-tracker example
#
#Copyright 2018 Simon D. Levy
#
# MIT License

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

mousetracker: mousetracker.o nengo_pidcontrol.o python_class.o
	g++ -o mousetracker mousetracker.o nengo_pidcontrol.o  python_class.o \
		-L$(PYTHON_LIBDIR) $(OPENCV_LINK) -lpython$(PYVER)

mousetracker.o: mousetracker.cpp nengo_pidcontrol.h
	g++ $(CFLAGS) -c -I $(PYINC) $(OPENCV_COMPILE) mousetracker.cpp 

commandline: commandline.o nengo_pidcontrol.o python_class.o
	g++ -o commandline commandline.o nengo_pidcontrol.o python_class.o \
		-L$(PYTHON_LIBDIR) -lpython$(PYVER)

commandline.o: commandline.cpp nengo_pidcontrol.h
	g++ $(CFLAGS) -c -I $(PYINC) commandline.cpp 

nengo_pidcontrol.o: nengo_pidcontrol.cpp nengo_pidcontrol.h
	g++ $(CFLAGS) -c -I $(PYINC) nengo_pidcontrol.cpp 

python_class.o: python_class.cpp python_class.h
	g++ $(CFLAGS) -c -I $(PYINC) python_class.cpp 

clean:
	rm -rf mousetracker *.o *~ __pycache__ *.pyc
