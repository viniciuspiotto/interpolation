#ifndef NEWTON_INTERPOLATION_H
#define NEWTON_INTERPOLATION_H

void calcule_split_difference_table(int n, double x[], double y[], double table[]);
void print_difference_table(int n, double x[], double table[]);
double horner_method(int n, double x[], double table[], double point);

#endif