//
// Created by stanislav on 04.11.2024.
//

#ifndef IO_FUNCTIONS_H
#define IO_FUNCTIONS_H

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

unsigned int validate_input(const char* formatSpecifier, void* value, char message[]);
void take_user_input(unsigned char* method, int* debug_mode, unsigned long* iterations_count);
void print_debug_info(unsigned int iteration, double xi);
void print_result(double xi, double time_elapsed);


#endif //IO_FUNCTIONS_H
