#ifndef CUBIC_SPLINE_H
#define CUBIC_SPLINE_H

void solve_tridiagonal_system(int n, double a[], double b[], double c[], double d[], double x[]);
void calculate_second_derivatives(int n, double x[], double y[], double m[]);
double cubic_spline_interpolation(int n, double x[], double y[], double m[], double x_eval);

#endif
