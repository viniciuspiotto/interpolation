#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "newton_interpolation.h"
#include "utils.h"
#include "lagrange.h"
#include "cubic_spline.h"

const double START = 1.0;
const double END = 10.0;
const double ESTIMATED_POINT = 2.5;

double f1(double x) {
    return (tan(pow(x, 3) * cos(x) * (3 * log(x) + sin(x)))) / (pow(x, 4) * exp(3 * x + 5));
}

double f2(double x) {
    return (pow(x, 3) * sin(log(1 + pow(x, 2) + pow(x, 8))))/ ((pow(x, 2) + 1) * sqrt(1 + pow(x, 2)));
}

int main () {
    int n_values[] = {5, 10, 15, 20, 30};
    int num_iterations = sizeof(n_values) / sizeof(n_values[0]);
    double real_value = f1(ESTIMATED_POINT);
    
    for (int i = 0; i < num_iterations; i++) {
        int n = n_values[i];
        double x[n];
        double y[n];
        generate_points(n, START, END, x, y, f1);

        // NEWTON
        double table[n * n];
        calcule_split_difference_table(n, x, y, table);
        double result_newton = horner_method(n, x, table, ESTIMATED_POINT);
        printf("NEWTON n = %d | error = %.20f\n", n, fabs(real_value - result_newton));

        // LAGRANGE
        double result_lagrange = calcule_lagrange(n, x, y, ESTIMATED_POINT);
        printf("LAGRANGE n = %d | error = %.20f\n", n, fabs(real_value - result_lagrange));

        // CUBIC SPLINE
        double *second_derivs = (double *)malloc(n * sizeof(double));
        calculate_second_derivatives(n, x, y, second_derivs);
        double result_cubic_spline = cubic_spline_interpolation(n, x, y, second_derivs, ESTIMATED_POINT);
        free(second_derivs);
        printf("CUBIC SPLINE n = %d | error = %.20f\n", n, fabs(real_value - result_cubic_spline));

        printf("\n");
    }

    return 0;
}