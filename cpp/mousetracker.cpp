/*
Simple C++/Nengo example using a PID controller to track mouse movement

Copyright 2018 Simon D. Levy

MIT License
*/

#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

// Params to play with
static const float Kp = 1.0;
static const float Kd = 1.0;
static const float sim_time = 0.001;

#include "nengo_pidcontrol.h"

static const int WIDTH  = 800;
static const int HEIGHT = 500;

// Start cursor in the center of the window
static float cursorpos[2] = {WIDTH/2, HEIGHT/2};

void mouse_callback(int  event, int  x, int  y, int  flag, void *param)
{
    if (event == EVENT_MOUSEMOVE) {
        cursorpos[0] = x;
        cursorpos[1] = y;
    }
}

#ifdef _WIN32
int WinMain(int argc, char ** argv)
#else
int main(int argc, char ** argv)
#endif
{    
    NengoPIDController controller = NengoPIDController(Kp, Kd, 0, 2, sim_time); // Ki=0, n_dims = 2
    namedWindow("pdcontrol");

    setMouseCallback("pdcontrol", mouse_callback);

    // Start circle position in the center of the window as well
    static float circlepos[2] = {WIDTH/2, HEIGHT/2};

    while (true) {

        // Create empty image
        Mat image = Mat::zeros(HEIGHT, WIDTH, CV_8UC3 );

        // Get the current cursor position from the callback and draw the square target there
        rectangle(image, Point(cursorpos[0]-10,cursorpos[1]-10), Point(cursorpos[0]+10,cursorpos[1]+10), Scalar(0,0,255), -1);

        // Use PID control to drive the circle toward the square
        float correction[2] = {0,0};
        controller.getCorrection(cursorpos, circlepos, correction);
        circlepos[0] += correction[0];
        circlepos[1] += correction[1];

        // Draw the circle in its current position
        circle(image, Point(circlepos[0], circlepos[1]), 10, Scalar(0, 255, 0), -1);

        // Display the image
        imshow("pdcontrol",image);

        // Pause briefly, exiting on ESC
        if (waitKey(10) == 27) break;
    }

    return 0;
}
