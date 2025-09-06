#include <stdio.h>
#include <math.h>
#include "newton_interpolation.h"
#include "utils.h"

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
    int n_values[] = {5, 10, 15};
    int num_iterations = sizeof(n_values) / sizeof(n_values[0]);
    
    for (int i = 0; i < num_iterations; i++) {
        int n = n_values[i];
        double x[n];
        double y[n];
        double table[n * n];
        generate_points(n, START, END, x, y, f1);

        // NEWTON
        calcule_split_difference_table(n, x, y, table);
        double result = horner_method(n, x, table, ESTIMATED_POINT);

        printf("using n = %d, estimated point in newton = %.20f\n", n, result);

        // LAGRANGE

        // CUBIC SPLINE
    }

    return 0;
}