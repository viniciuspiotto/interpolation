#include "functions.h"
#include <math.h>

double polynomial_function(double x) {
    return pow(x, 3) - 2 * pow(x, 2) + 5;
}

double trigonometric_function(double x) {
    return sin(2 * x) + cos(x);
}

double exponential_function(double x) {
    return exp(x / 2.0);
}

double logarithmic_function(double x) {
    if (x <= -1.0) {
        return 0.0;
    }
    return log(x + 1.0);
}

double runge_function(double x) {
    return 1.0 / (1.0 + 25.0 * pow(x, 2));
}

double step_function(double x) {
    double change_point = -0.7;
    if (x < change_point) {
        return 0.0;
    } else {
        return 1.0;
    }
}
