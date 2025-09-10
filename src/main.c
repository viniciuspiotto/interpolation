#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "newton_interpolation.h"
#include "utils.h"
#include "lagrange.h"
#include "cubic_spline.h"
#include "functions.h"

const double START = -1;
const double END = 1;
const int FUNCTION_AMOUNT = 6;
const int NUM_EVALS = 10000;

typedef struct {
    double (*func_ptr)(double);
    const char *name;
} TestFunction;

int main () {
    FILE *complexing_time, *error;
    int n_values[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int num_iterations = sizeof(n_values) / sizeof(n_values[0]);
    double eval_points[NUM_EVALS];
    for (int i = 0; i < NUM_EVALS; i++) {
        eval_points[i] = START + (END - START) * (rand() / (double)RAND_MAX);
    }

    complexing_time = fopen("complex.csv", "w");
    error = fopen("error.csv", "w");

    fprintf(complexing_time,"Method,Function,N,Total_time\n");
    fprintf(error,"Method,Function,N,Mean_error\n");

    TestFunction test_functions[] = {
        { polynomial_function, "Polinomial" },
        { trigonometric_function, "Trigonométrico" },
        { exponential_function, "Exponencial" },
        { logarithmic_function, "Logaritmo" },
        { runge_function, "Runge" },
        { step_function, "Degrau" }
    };
    
    for (int j = 0; j < FUNCTION_AMOUNT; j++) {
        for (int i = 0; i < num_iterations; i++) {
                int n = n_values[i];
                double x[n];
                double y[n];
                generate_points(n, START, END, x, y, test_functions[j].func_ptr);

                double start_time, end_time, total_time;

                // NEWTON
                start_time = get_time();
                double newton_table[n * n];
                calcule_split_difference_table(n, x, y, newton_table);
                end_time = get_time();
                total_time = end_time - start_time;

                start_time = get_time();
                double sum_newton = 0.0;
                double real_value = 0.0;
                for (int k = 0; k < NUM_EVALS; k++) {
                    real_value = test_functions[j].func_ptr(eval_points[k]);
                    sum_newton += fabs(horner_method(n, x, newton_table, eval_points[k]) - real_value);
                }
                fprintf(error,"Newton,%s,%d,%.9f\n", test_functions[j].name,n, sum_newton/NUM_EVALS);
                end_time = get_time();
                total_time += end_time - start_time;
                fprintf(complexing_time,"Newton,%s,%d,%.9f\n",test_functions[j].name, n, total_time);

                // LAGRANGE
                start_time = get_time();
                double response_lagrange = 0.0;
                for (int k = 0; k < NUM_EVALS; k++) {
                    real_value = test_functions[j].func_ptr(eval_points[k]);
                    response_lagrange += fabs(calcule_lagrange(n, x, y, eval_points[k]) - real_value);
                }
                fprintf(error,"Lagrange,%s,%d,%.9f\n",test_functions[j].name, n, response_lagrange/NUM_EVALS);
                end_time = get_time();
                total_time = end_time - start_time;
                fprintf(complexing_time,"Lagrange,%s,%d,%.9f\n",test_functions[j].name, n, total_time);

                // CUBIC SPLINE
                start_time = get_time();
                double *second_derivs = (double *)malloc(n * sizeof(double));
                end_time = get_time();
                total_time = end_time - start_time;

                start_time = get_time();
                double response_cubic_spline = 0.0;
                for (int k = 0; k < NUM_EVALS; k++) {
                    real_value = test_functions[j].func_ptr(eval_points[k]);
                    response_cubic_spline += fabs(cubic_spline_interpolation(n, x, y, second_derivs, eval_points[k]) - real_value);
                }
                fprintf(error,"Cubic_Spline,%s,%d,%.9f\n",test_functions[j].name, n, response_cubic_spline/NUM_EVALS);
                end_time = get_time();
                total_time += end_time - start_time;
                fprintf(complexing_time,"Cubic_Spline,%s,%d,%.9f\n",test_functions[j].name, n, total_time);
                free(second_derivs);
            }
    }
    fclose(complexing_time);
    fclose(error);
    return 0;
}