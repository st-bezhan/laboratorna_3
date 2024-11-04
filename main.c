// FUNCTION x^4 - 5x^3 - 0,25x^2 + 2;
// EQUATION f(x) = 0;
// X = 0,75 -> f(x) = 0,066
// X = 0,760 -> f(x) = -0.006
// Interval of isolation [3;6]

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const double EPSILON = 1e-6;
const double left_isolation_border = 3; // x0
const double right_isolation_border = 6; // x1

unsigned int validate_input(const char* formatSpecifier, void* value, char message[]);
void take_user_input(int* debug_mode, unsigned long* iterations_count);

double math_function(double x);

double secant(double x0, double x1, unsigned int debug_mode, unsigned long max_iterations); // Метод хорд
double bisect(); // Метод половинного ділення

int main() {
    unsigned long max_amount_iterations = 0;
    unsigned int debug_mode = 0;

    take_user_input(&debug_mode, &max_amount_iterations);
    double res = secant(left_isolation_border, right_isolation_border, debug_mode, max_amount_iterations);
    printf("\nRes = %lf\n", res);
    double res0 = math_function(res);
    printf("Math_function(res) = %lf\n", res0);
}

unsigned int validate_input(const char* formatSpecifier, void* value, char message[]) {
    char input[100];

    printf("%s", message);
    do {
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, formatSpecifier, value) == 1) {
            return 1;
        } else {
            printf("\nInvalid input, try again");
            printf("%s", message);
            fseek(stdin, 0, SEEK_END); //clears buffer
        }
    } while (1);
}

void take_user_input(int* debug_mode, unsigned long* iterations_count) {
    do {
        validate_input("%u", debug_mode, "\nБажаєте увімкнути режим відладки?\n"
                                      "[0] - Ні\n"
                                      "[1] - Так\n");
        printf("DEBUG = %d", *debug_mode);
        if (*debug_mode == 0 || *debug_mode == 1) {
            break;
        }
    } while (1);

    validate_input("%lu", iterations_count, "\nВведіть кількість ітерацій: ");
}

double math_function(double x) {
    return pow(x, 4) - 5 * pow(x, 3) - 0.25 * pow(x, 2) + 2;
}

double secant(double x0, double x1, unsigned int debug_mode, unsigned long max_iterations) {
    unsigned int current_iteration = 1;
    double xi;
    clock_t clock_start;

    if (!debug_mode) {
        clock_start = clock();
    }

    while (current_iteration <= max_iterations) {
        xi = (math_function(x1) * x0 - math_function(x0) * x1) / (math_function(x1) - math_function(x0));

        if (debug_mode) {
            printf("\nІтерація: %u, Значення: %lf", current_iteration, xi);
        }

        if (math_function(xi) * math_function(x0) < 0) { // Перевірка чи мають f(xi) та f(x0) різні знаки
            x1 = xi;
        } else {
            x0 = xi;
        }

        current_iteration++;
    }

    if (fabs(x1 - x0) <= EPSILON) {
        printf("\nF(x) = 0 у точці %lf", xi);
        exit(1);
    } else {

    }

    if (!debug_mode) {
        clock_t clock_stop = clock();
        double execution_time = (double)(clock_stop - clock_start) / CLOCKS_PER_SEC;
        printf("Часу витрачено на пошук кореня: %lf секунд.", execution_time);
    }

    return xi;
}
