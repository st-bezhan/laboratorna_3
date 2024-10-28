#include <math.h>
#include <stdio.h>

// FUNCTION x^4 - 5x^3 - 0,25x^2 + 2;
// EQUATION f(x) = 0;
// X = 0,75 -> f(x) = 0,066
// X = 0,760 -> f(x) = -0.006

double intial_function(double x);
double functions_first_derivative(double x);
double functions_second_derivative(double x);

unsigned int validate_input(const char* formatSpecifier, void* value, char message[]);

void define_intervals();
void check_for_sign_change(double left_border, double right_border, unsigned long int intervals);

int main(void) {
    define_intervals();
    return 0;
}


double initial_function(double x)  {
    return pow(x, 4) - 5 * pow(x, 3) - 0,25 * pow(x, 2) + 2;
}

double functions_first_derivative(double x) {

}

double functions_second_derivative(double x) {

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

void define_intervals() {
    double left_border = 0;
    double right_border = 0;
    double intervals = 0;
    validate_input("%lf", &left_border,
        "\nType in value for left border of interval: ");
    do {
        validate_input("%lf", &right_border,
       "\nType in value for right border of interval (>Left border): ");
    } while (right_border <= left_border);
    while (intervals <= 0) {
        validate_input("%lu", &intervals,
        "\nType in amount of intervals to find sign changes in them: ");
    }

    check_for_sign_change(left_border, right_border, intervals);
}

void check_for_sign_change(double left_border, double right_border, unsigned long int intervals) {
    double step = (right_border - left_border) / intervals;
    double current_x = left_border;
    double fX;

    unsigned int change_sign_counter = -1;
    unsigned int current_step = 0;
    unsigned char previous_sign;
    unsigned char current_sign; // 1 > 0; 0 < 0;;; 1 == +; 0 == -;

    while (current_step <= intervals) {
        fX = initial_function(current_x);
        current_x += step;

        previous_sign = current_sign;
        current_sign = fX >= 0 ? 1 : 0;
        printf("\nCurrent sign: %u", current_sign);

        if (previous_sign != current_sign) {
            change_sign_counter++;
            if (change_sign_counter != 0) {
                printf("\nSign changed");
            }
        }

        current_step++;
    }
}