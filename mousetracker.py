#!/usr/bin/env python3
'''
Simple PD control example using a mouse cursor in OpenCV

Copyright 2018 Melanie Jouaiti and Simon D. Levy

This file is part of HackflightNengo.

HackflightNengo is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as 
published by the Free Software Foundation, either version 3 of the 
License, or (at your option) any later version.
This code is distributed in the hope that it will be useful,     
but WITHOUT ANY WARRANTY without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License 
along with this code.  If not, see <http:#www.gnu.org/licenses/>.
'''

import cv2
import numpy as np
from nengo_pidcontrol import PIDController as Controller
import numpy as np

# Create an empty image
image = np.zeros((500, 800, 3), np.uint8)

# Create a PD controller to track the cursor
controller = Controller(1, 1, n_dims=2)

# Mouse-movement callback; sets position of square target
def cursor(event, x, y, flags, cursorpos):
    cursorpos[0] = int(x)
    cursorpos[1] = int(y)

# Compute the center point of the image
cx, cy = image.shape[1]/2, image.shape[0]/2

# Initial circle position is in the center of the screen
circlepos = np.array([cx,cy]).astype('int64')

# Start cursor target in the center as well; will be updated by mouse-movement callback
cursorpos = np.array([cx,cy]).astype('int64')

# Create a window and set its mouse-movement callback
cv2.namedWindow("pdcontrol")
cv2.setMouseCallback("pdcontrol", cursor, cursorpos)

while True:

    # Clear the image
    image[:] = (0, 0, 0)

    # Use PID control to drive the circle toward the square
    correction = controller.getCorrection(cursorpos, circlepos)
    circlepos += np.round(correction).astype('int64')

    # Get the current cursor position from the callback and draw the square target there
    x, y = cursorpos
    cv2.rectangle(image, (x-10,y-10), (x+10,y+10), (0,0,255), -1)

    # Draw the circle in its current position
    cv2.circle(image, (circlepos[0], circlepos[1]), 10, (0, 255, 0), -1)

    # Display the image
    cv2.imshow("pdcontrol", image)

    # Pause briefly, exiting on ESC
    if cv2.waitKey(1) & 0xFF == 27: 
        break
