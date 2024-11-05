//
// Created by stanislav on 04.11.2024.
//

#ifndef CALCULATION_FUNCTIONS_H
#define CALCULATION_FUNCTIONS_H
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

double math_function(double x);
void update_points(double *x0, double *x1, double xi);
unsigned int check_continue(unsigned int current_iteration, unsigned long *max_iterations, unsigned long initial_max_iterations);

double calculate_root(double x0, double x1, unsigned int debug_mode, unsigned long initial_max_iterations, unsigned char method); // main calc function


#endif //CALCULATION_FUNCTIONS_H
