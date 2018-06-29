## About

This repository shows how you can write C++ programs that work with the
Python-based [Nengo](https://www.nengo.ai/) neural simulator created at the University of Waterloo 
[Center for Theoretical Neuroscience](https://uwaterloo.ca/centre-for-theoretical-neuroscience/).  My
motivation for doing this is to call Nengo routines from the C++-based 
[Unreal Engine 4](https://www.unrealengine.com/en-US/what-is-unreal-engine-4) game-development platform; however
the example provided here shows a general way to make C++ programs run
Python code directly, without communication over a socket, remote procedure calls, and the like.

## Requirements

* [Python](https://www.python.org/downloads/) We're using Python3.6

* [Nengo](https://www.nengo.ai/download.html)

* The Python3 development environment.  This is OS-dependent.  On OS X, this package is included when you use 
[brew](https://brew.sh) to install Python.  On Ubuntu, I installed it using <tt>sudo apt install python3.6-dev</tt>.


## Command-line example

The first example is a simple command-line program that allows you to specify a one-dimensional (scalar) target value.
Starting with an actual value of zero, the program runs the PID controller on the target and actual values, 
adding the resulting correction to the actual value, and halting when the actual value comes within one percent of the 
target value.  

Before running this program in C++, you should first test the code in the <b>python</b> folder:

<pre>
  python3 commandline.py
</pre>

Once the example is running, you'll want to install the <b>nengo_pidcontrol.py</b> module so that it can be
accessed from anywhere on your file system:

<pre>
  sudo python3 setup.py install
</pre>

To build the command-line example on Linux (and Mac OS, assuming you've installed the 
[command-line tools](http://osxdaily.com/2014/02/12/install-command-line-tools-mac-os-x/)), you can 
run the following in the <b>cpp</b> folder:
<pre>
  make commandline
</pre>
and run it by typing
<pre>
  ./commandline
</pre>

On Windows, you can double-click the <b>CommandLine.sln</b> icon in <b>cpp\windows\CommandLine</b> to launch 
VisualStudio and run the program.

## Mouse-tracker example

The second example program is a simple two-dimensional position-tracking task (&ldquo;mousetracker&rdquo;) using 
[PID control](https://en.wikipedia.org/wiki/PID_controller).  You use the mouse to move little green square
around, and the PID controller adjusts the position of a little red circle so that it follows the square.
We wrote this example using [OpenCV](https://opencv.org/about.html), because of
how easy OpenCV makes it to do these sorts of animations.  So if you want to
try this example, you'll need to install OpenCV as well.  The make/run
procedure is the same as for the command-line example, except that on Windows
the first thing you should do is open the folder
<bThirdParty\OpenCV\Libraries\Win64</b>, copy the file
<b>opencv_world340.dll</b>, and paste it into the <b>C:\Windows\System32</b>
folder.  This will also help with any future programs you write using OpenCV.


## Writing your own applications

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

5. Write a C++ [example](https://github.com/simondlevy/NengoCPP/blob/master/mousetracker.cpp) to test your C++ class.

Although Nengo is built on the NumPy package and uses NumPy arrays as its common data structure, out PIDController class
API uses standard Python tuples, instead of NumPy arrays, to pass parameters and return results.  This approach
simplifies the work required by the C++ code for interacting with Python.

## Acknowledgements

Thanks to [Terry Stewart](http://compneuro.uwaterloo.ca/people/terrence-c-stewart.html) for help with the PID control
code, and to Chris Eliasmith and the organizers of Nengo Summer School 2018 for introducing us to Nengo.
