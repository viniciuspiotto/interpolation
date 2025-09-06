#include "utils.h"

void generate_points(int n, double start, double end, double x[], double y[], double (*func)(double)) {
    double h = (end - start) / (n - 1);

    for (int i = 0; i < n; i++) {
        x[i] = start + i * h;
        y[i] = func(x[i]);
    }
}