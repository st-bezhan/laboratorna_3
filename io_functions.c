//
// Created by stanislav on 04.11.2024.
//

#include "io_functions.h"
#include "calculation_functions.h"

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

void take_user_input(unsigned char* method, int* debug_mode, unsigned long* iterations_count) {
    do {
        validate_input("%d", method, "\nОберіть варіант:\n"
                                     "[0] - Метод хорд\n"
                                     "[1] - Метод половинного ділення");
    } while (*method != 0 && *method != 1);

    do {
        validate_input("%u", debug_mode, "\nБажаєте увімкнути режим відладки?\n"
                                      "[0] - Ні\n"
                                      "[1] - Так\n");
    } while (*debug_mode != 0 && *debug_mode != 1);

    validate_input("%lu", iterations_count, "\nВведіть кількість ітерацій: ");
}

void print_debug_info(unsigned int iteration, double xi) {
    printf("\nІтерація: %u, Значення: %lf", iteration, xi);
}

void print_result(double xi, double time_elapsed) {
    printf("\nЗнайдене значення корення: %lf"
       "\nЗначення функції в цій точці: %lf", xi, math_function(xi));
    printf("\nВитрачено часу на знаходження кореня: %lf секунд.", time_elapsed);
}