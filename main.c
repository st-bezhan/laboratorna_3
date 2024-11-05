// FUNCTION x^4 - 5x^3 - 0,25x^2 + 2;
// EQUATION f(x) = 0;
// X = 0,75 -> f(x) = 0,066
// X = 0,760 -> f(x) = -0.006
// Interval of isolation [3;6]

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "calculation_functions.h"
#include "io_functions.h"

// const double left_isolation_border = 3; // x0
// const double right_isolation_border = 6; // x1

int main() {
    system("chcp 65001"); // Некоректне кодування виводу в консоль після переносу проекта з макбука
    unsigned long max_amount_iterations = 0;
    unsigned int debug_mode = 0;
    unsigned char method = 0;

    take_user_input(&method, &debug_mode, &max_amount_iterations);
    calculate_root(1, 10, debug_mode, max_amount_iterations, method);
}







