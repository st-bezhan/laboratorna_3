//
// Created by stanislav on 04.11.2024.
//
#include "calculation_functions.h"
#include "io_functions.h"
// #include <sys\time.h>

const double EPSILON = 1e-6;

double math_function(double x) {
    return pow(x, 4) - 5 * pow(x, 3) - 0.25 * pow(x, 2) + 2;
}

// method 0 = secant; method 1 = bisect;
double calculate_root(double x0, double x1, unsigned int debug_mode, unsigned long initial_max_iterations, unsigned char method) {
    clock_t function_start = clock();
    struct timespec begin, end;
    unsigned int current_iteration = 1;
    unsigned long iterations_limit = initial_max_iterations;
    double xi;
    volatile double time_elapsed = 0.0;

    while (fabs(x1 - x0) >= EPSILON &&
        round(math_function(x0) * 10000000) / 10000000 != 0 && // Перевірка для уникнення ситуацій
        round(math_function(x1) * 10000000) / 10000000!= -0) { // з майже нескінченним циклом

        if (method == 0) {
            clock_gettime(CLOCK_MONOTONIC, &begin); //clock() - недостатньо точний, не помічає малих значень
            xi = (math_function(x1) * x0 - math_function(x0) * x1) / (math_function(x1) - math_function(x0)); // secant
            clock_gettime(CLOCK_MONOTONIC, &end);
        } else if (method == 1) {
            clock_gettime(CLOCK_MONOTONIC, &begin);
            xi = (x0 + x1) / 2; // bisect
            clock_gettime(CLOCK_MONOTONIC, &end);
        }

        clock_gettime(CLOCK_MONOTONIC, &begin); //clock() - недостатньо точний, не помічає малих значень
        xi = (math_function(x1) * x0 - math_function(x0) * x1) / (math_function(x1) - math_function(x0));
        clock_gettime(CLOCK_MONOTONIC, &end);

        time_elapsed += (end.tv_nsec - begin.tv_nsec) / 1000000000.0 + (end.tv_sec  - begin.tv_sec);
        update_points(&x0, &x1, xi);

        if (debug_mode) {
            print_debug_info(current_iteration, xi);
        }

        if (current_iteration == iterations_limit) {
            unsigned int action_selection = check_continue(current_iteration, &iterations_limit, initial_max_iterations);
            if (action_selection == 3) {
                printf("\nЧасу витрачено на всю функцію: %lf", ((double)(clock() - function_start) / CLOCKS_PER_SEC));
                print_result(xi, time_elapsed);
                exit(0);
            }
        }
        printf("\n%lf", time_elapsed);
        current_iteration++;
    }
    printf("\nЧасу витрачено на всю функцію: %lf", ((double)(clock() - function_start) / CLOCKS_PER_SEC));
    print_result(xi, time_elapsed);
    return xi;
}

void update_points(double *x0, double *x1, double xi) {
    if (math_function(xi) * math_function(*x0) < 0) {
        *x1 = xi;
    } else {
        *x0 = xi;
    }
}

unsigned int check_continue(unsigned int current_iteration, unsigned long *max_iterations, unsigned long initial_max_iterations) {
    unsigned int action_selection;
    do {
        printf("\nЗдійснено задану кількість ітерацій :%u"
           "\n[1] - Продовжити з такою ж кількістю ітерацій"
           "\n[2] - Виконати програму до кінця, поки не буде знайдено корінь рівняння"
           "\n[3] - Вийти із програми\n", current_iteration);
        validate_input("%u", &action_selection, "");
    } while (action_selection != 1 && action_selection != 2 && action_selection != 3);

    if (action_selection == 1) {
        *max_iterations += initial_max_iterations;
    }

    return action_selection;
}