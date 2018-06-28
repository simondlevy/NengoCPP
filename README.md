# About

This repository shows how you can write C++ programs that work with the the
Python-based [Nengo](https://www.nengo.ai/) neural simulator created at the University of Waterloo 
[Center for Theoretical Neuroscience](https://uwaterloo.ca/centre-for-theoretical-neuroscience/).  My
motivation for doing this is to call Nengo routines from the C++-based 
[Unreal Engine 4](https://www.unrealengine.com/en-US/what-is-unreal-engine-4) game-development platform; however
the example provided here shows a general way to can make C++ programs run
Python code directly, without communication over a socket, remote procedure calls, and the like.

# Requirements

* [Python](https://www.python.org/downloads/) We're using Python3.6

* [Nengo](https://www.nengo.ai/download.html)

# Command-line example

# Mouse-tracker example

Our second example program is a simple two-dimensional position-tracking task (&ldquo;mousetracker&rdquo;) using 
[PID control](https://en.wikipedia.org/wiki/PID_controller).  You use the mouse to move little green square
around, and the PID controller adjusts the position of a little red circle so that it follows the square.
We wrote this example using [OpenCV](https://opencv.org/about.html), because of how easy it is to do these sorts
of animations.  So if you want to try this example, you'll need to install OpenCV as well.

# Writing your own applications

To use our PID-control example as the basis for developing your own C++/Nengo projects, it will be
helpful to understand how we developed our code:

1. Use the [Nengo GUI](https://github.com/nengo/nengo-gui) to prototype your neural model interactively.

2. Package up your Nengo model into a Python class.  In our 
[PIDController](https://github.com/simondlevy/NengoCPP/blob/master/nengo_pidcontrol.py) class, we 
set up the constructor method with a boolean flag 
[in\_gui](https://github.com/simondlevy/NengoCPP/blob/master/nengo_pidcontrol.py#L83-L86) 
(default = False), which allows us to continue to visualize the model by running a simple 
[script](https://github.com/simondlevy/NengoCPP/blob/master/gui_demo.py) from the command-line:
<tt>nengo gui\_demo.py</tt>

3. Write a [Python program](https://github.com/simondlevy/NengoCPP/blob/master/mousetracker.py) 
to test your Python class.  

4. Write a C++ class (
[API](https://github.com/simondlevy/NengoCPP/blob/master/nengo_pidcontrol.h)
and [implementation](https://github.com/simondlevy/NengoCPP/blob/master/nengo_pidcontrol.cpp)
), each of whose methods corresponds to a method in your Python class.
