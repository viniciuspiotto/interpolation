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

int main () {
    FILE *complexing_time, *error;
    int n_values[] = {10, 50, 100, 200, 500, 1000};
    int num_iterations = sizeof(n_values) / sizeof(n_values[0]);
    double eval_points[NUM_EVALS];
    for (int i = 0; i < NUM_EVALS; i++) {
        eval_points[i] = START + (END - START) * (rand() / (double)RAND_MAX);
    }

    complexing_time = fopen("complex.csv", "w");
    error = fopen("error.csv", "w");

    fprintf(complexing_time,"Method,Scenarios,N,Total_time,Mean_time\n");
    fprintf(error,"Method,N,Mean_error\n");

    double (*functions[])(double) = {polynomial_function, trigonometric_function, exponential_function, logarithmic_function, runge_function, step_function};
    
    for (int j = 0; j < FUNCTION_AMOUNT; j++) {
        for (int i = 0; i < num_iterations; i++) {
                int n = n_values[i];
                double x[n];
                double y[n];
                generate_points(n, START, END, x, y, functions[j]);

                double start_time, end_time, total_time;

                // NEWTON
                
                // Pre-processing
                start_time = get_time();
                double newton_table[n * n];
                calcule_split_difference_table(n, x, y, newton_table);
                end_time = get_time();
                total_time = end_time - start_time;
                fprintf(complexing_time,"Newton,Pre-processing,%d,%.9f,N/A\n", n, total_time);

                // Mean
                start_time = get_time();
                double sum_newton = 0.0;
                double real_value = 0.0;
                for (int k = 0; k < NUM_EVALS; k++) {
                    real_value = functions[j](eval_points[k]);
                    sum_newton += fabs(horner_method(n, x, newton_table, eval_points[k]) - real_value);
                }
                fprintf(error,"Newton,%d,%.9f\n", n, sum_newton/NUM_EVALS);
                end_time = get_time();
                total_time = end_time - start_time;
                fprintf(complexing_time,"Newton,Mean,%d,%.9f,%.9f\n", n, total_time, total_time / NUM_EVALS);

                // Single
                start_time = get_time();
                calcule_split_difference_table(n, x, y, newton_table);
                horner_method(n, x, newton_table, eval_points[0]);
                end_time = get_time();
                total_time = end_time - start_time;
                fprintf(complexing_time,"Newton,Single,%d,%.9f,%.9f\n", n, total_time, total_time);

                // LAGRANGE

                // Pre-processing
                fprintf(complexing_time,"Lagrange,Pre-processing,%d,N/A,N/A\n", n);

                // Mean
                start_time = get_time();
                double response_lagrange = 0.0;
                for (int k = 0; k < NUM_EVALS; k++) {
                    real_value = functions[j](eval_points[k]);
                    response_lagrange += fabs(calcule_lagrange(n, x, y, eval_points[k]) - real_value);
                }
                fprintf(error,"Lagrange,%d,%.9f\n", n, response_lagrange/NUM_EVALS);
                end_time = get_time();
                total_time = end_time - start_time;
                fprintf(complexing_time,"Lagrange,Mean,%d,%.9f,%.9f\n", n, total_time, total_time / NUM_EVALS);

                // Single
                start_time = get_time();
                calcule_lagrange(n, x, y, eval_points[0]);
                end_time = get_time();
                total_time = end_time - start_time;
                fprintf(complexing_time,"Lagrange,Single,%d,%.9f,%.9f\n", n, total_time, total_time);

                // CUBIC SPLINE

                // Pre-processing
                start_time = get_time();
                double *second_derivs = (double *)malloc(n * sizeof(double));
                end_time = get_time();
                total_time = end_time - start_time;
                fprintf(complexing_time,"Cubic Spline,Pre-processing,%d,%.9f,N/A\n", n, total_time);

                // Mean
                start_time = get_time();
                double response_cubic_spline = 0.0;
                for (int k = 0; k < NUM_EVALS; k++) {
                    real_value = functions[j](eval_points[k]);
                    response_cubic_spline += fabs(cubic_spline_interpolation(n, x, y, second_derivs, eval_points[k]) - real_value);
                }
                fprintf(error,"Cubic_Spline,%d,%.9f\n", n, response_cubic_spline/NUM_EVALS);
                end_time = get_time();
                total_time = end_time - start_time;
                fprintf(complexing_time,"Cubic Spline,Mean,%d,%.9f,N/A\n", n, total_time);

                // Single
                start_time = get_time();
                calculate_second_derivatives(n, x, y, second_derivs);
                cubic_spline_interpolation(n, x, y, second_derivs, eval_points[0]);
                end_time = get_time();
                total_time = end_time - start_time;
                fprintf(complexing_time,"Cubic Spline,Single,%d,%.9f,%.9f\n", n, total_time, total_time);

                free(second_derivs);
            }
    }
    fclose(complexing_time);
    fclose(error);
    return 0;
}