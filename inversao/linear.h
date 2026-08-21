#ifndef __LINEAR_H__
#define __LINEAR_H__

#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utils.h"

void eliminacaoGauss(double **A, double *b, int n);
void retrossubs(double **A, double *b, double *x, int n);
void resolveSL(double **A, double *b, double *x, int n);
void L_y_b (double **L, double *y, double *b, int n);
void U_x_y (double **U, double *x, double *y, int n);
void resolveInvert (double **A, double **L, double **U, double **Inv, int n);
void printMatriz (double **A, int n);

#endif // __LINEAR_H__

