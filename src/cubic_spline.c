#include <stdlib.h>
#include "cubic_spline.h"

void solve_tridiagonal_system(int n, double a[], double b[], double c[], double d[], double x[]) {
    double *c_prime = (double *)malloc(n * sizeof(double));
    double *d_prime = (double *)malloc(n * sizeof(double));

    c_prime[0] = c[0] / b[0];
    d_prime[0] = d[0] / b[0];

    for (int i = 1; i < n; i++) {
        double m = 1.0 / (b[i] - a[i] * c_prime[i - 1]);
        c_prime[i] = c[i] * m;
        d_prime[i] = (d[i] - a[i] * d_prime[i - 1]) * m;
    }

    x[n - 1] = d_prime[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        x[i] = d_prime[i] - c_prime[i] * x[i + 1];
    }

    free(c_prime);
    free(d_prime);
}

void calculate_second_derivatives(int n, double x[], double y[], double m[]) {
    int size = n - 2;
    double *a = (double *)malloc(size * sizeof(double));
    double *b = (double *)malloc(size * sizeof(double));
    double *c = (double *)malloc(size * sizeof(double));
    double *d = (double *)malloc(size * sizeof(double));
    double *m_internal = (double *)malloc(size * sizeof(double));

    for (int i = 0; i < size; i++) {
        double h1 = x[i + 1] - x[i];
        double h2 = x[i + 2] - x[i + 1];
        a[i] = h1;
        b[i] = 2 * (h1 + h2);
        c[i] = h2;
        d[i] = 6 * ((y[i + 2] - y[i + 1]) / h2 - (y[i + 1] - y[i]) / h1);
    }

    solve_tridiagonal_system(size, a, b, c, d, m_internal);

    m[0] = 0;
    m[n - 1] = 0;
    for (int i = 0; i < size; i++) {
        m[i + 1] = m_internal[i];
    }

    free(a);
    free(b);
    free(c);
    free(d);
    free(m_internal);
}

double cubic_spline_interpolation(int n, double x[], double y[], double m[], double x_eval) {
    int i = 0;
    while (i < n - 1 && x_eval > x[i + 1]) {
        i++;
    }

    double h = x[i + 1] - x[i];
    double term1 = (m[i] / (6 * h)) * (x[i + 1] - x_eval) * (x[i + 1] - x_eval) * (x[i + 1] - x_eval);
    double term2 = (m[i + 1] / (6 * h)) * (x_eval - x[i]) * (x_eval - x[i]) * (x_eval - x[i]);
    double term3 = ((y[i] / h) - (m[i] * h / 6)) * (x[i + 1] - x_eval);
    double term4 = ((y[i + 1] / h) - (m[i + 1] * h / 6)) * (x_eval - x[i]);
    
    return term1 + term2 + term3 + term4;
}