#define _POSIX_C_SOURCE 200809L
#include "utils.h"
#include <time.h>

void generate_points(int n, double start, double end, double x[], double y[], double (*func)(double)) {
    double h = (end - start) / (n - 1);

    for (int i = 0; i < n; i++) {
        x[i] = start + i * h;
        y[i] = func(x[i]);
    }
}

double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}