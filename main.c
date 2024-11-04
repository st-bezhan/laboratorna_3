// FUNCTION x^4 - 5x^3 - 0,25x^2 + 2;
// EQUATION f(x) = 0;
// X = 0,75 -> f(x) = 0,066
// X = 0,760 -> f(x) = -0.006
// Interval of isolation [3;10]

#include <math.h>
#include <stdio.h>

const double EPSILON = 1e-6;
const double left_isolation_border = 3; // x0
const double right_isolation_border = 6; // x1

unsigned int validate_input(const char* formatSpecifier, void* value, char message[]);
void take_user_input(unsigned int* debug_mode, unsigned int* iterations_count);

double math_function(double x);
// double analytical_first_derivative(double x);
// double analytical_second_derivative(double x);

double secant(double x0, double x1, unsigned int debug_mode, unsigned int max_iterations); // Метод хорд
double bisect(); // Метод половинного ділення

int main() {
    unsigned int max_iterations;
    unsigned int debug_mode;

    take_user_input(&debug_mode, &math_function);
    printf("Проміжок ізоляції: [%lf;%lf]\n", left_isolation_border, right_isolation_border);
    printf("Point %lf %lf\n", left_isolation_border, math_function(left_isolation_border));
    printf("Point %lf %lf\n", right_isolation_border, math_function(right_isolation_border));
    double res = secant(left_isolation_border, right_isolation_border, debug_mode, max_iterations);
    printf("Res = %lf\n", res);
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

void take_user_input(unsigned int* debug_mode, unsigned int* iterations_count) {
    validate_input("%u", &debug_mode, "\nБажаєте увімкнути режим відладки?\n"
                                      "[0] - Ні\n"
                                      "[1] - Так\n");
    validate_input("%u", &iterations_count, "\nВведіть максимальну кількість ітерацій:");
}

double math_function(double x) {
    return pow(x, 4) - 5 * pow(x, 3) - 0.25 * pow(x, 2) + 2;
}

double secant(double x0, double x1, unsigned int debug_mode, unsigned int max_iterations) {
    unsigned int current_iteration = 0;
    double xi;

    while (fabs(x1 - x0) >= EPSILON && current_iteration < 100) {
        xi = (math_function(x1) * x0 - math_function(x0) * x1) / (math_function(x1) - math_function(x0));

        if (math_function(xi) * math_function(x0) < 0) { // Перевірка чи мають f(xi) та f(x0) різні знаки
            x1 = xi;
        } else {
            x0 = xi;
        }
        current_iteration++;
    }

    return xi;
}
