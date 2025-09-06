#include <stdio.h>
#include "newton_interpolation.h"

void calcule_split_difference_table(int n, double x[], double y[], double table[]) {
    for (int i = 0; i < n; i++) {
        table[i * n + 0] = y[i];
    }

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            double term1 = table[(i + 1) * n + (j - 1)];
            double term2 = table[i * n + (j - 1)];
            table[i * n + j] = (term1 - term2) / (x[i + j] - x[i]);
        }
    }
}

void print_difference_table(int n, double x[], double table[]) {
    printf("Tabela de Diferencas Divididas:\n");
    for (int i = 0; i < n; i++) {
        printf("x=%.1f | ", x[i]);
        for (int j = 0; j < n - i; j++) {
            printf("%10.4f ", table[i * n + j]);
        }
        printf("\n");
    }
}

double horner_method(int n, double x[], double table[], double point) {
    double result = table[n - 1];

    for (int i = n - 2; i >= 0; i--) {
        result = result * (point - x[i]) + table[i];
    }
    return result;
}