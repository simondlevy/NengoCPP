/*
Simple C++/Nengo example using command-line i/o

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

// Params to play with
static const float Kp = 1.0;
static const float Kd = 1.0;
static const float sim_time = 0.001;

#include "nengo_pidcontrol.h"
#include <stdio.h>

int main(int argc, char ** argv)
{    
    NengoPIDController controller = NengoPIDController(Kp, Kd, 0, 1, sim_time); // Ki=0, n_dims = 2

    while (true) {

	printf("Enter a target value (or non-number to quit) > ");
	float target = 0;
	if (scanf("%f", &target) < 1) break;

		
    }

    return 0;
}
