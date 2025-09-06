#include "lagrange.h"

double calcule_lagrange(int n, double x[], double y[], double point) {
    double result = 0.0;

    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term = (term * (point - x[j])) / (x[i] - x[j]); 
            }
        }
        result += term;
    }

    return result;
}