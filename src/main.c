#include <stdio.h>
#include <math.h>

double f1(double x) {
    return (tan(pow(x, 3) * cos(x) * (3 * log(x) + sin(x)))) / (pow(x, 4) * exp(3 * x + 5));
}

double f2(double x) {
    return (pow(x, 3) * sin(log(1 + pow(x, 2) + pow(x, 8))))/ ((pow(x, 2) + 1) * sqrt(1 + pow(x, 2)));
}

int main () {

    printf("%.2f\n", f1(0.01));
    printf("%.2f\n", f2(0.01));

    return 0;
}