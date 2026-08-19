#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utils.h"

void eliminacaoGauss(double **A, double *b, int n) {
  for (int i = 0; i < n; ++i) {
    int iMax = i;
    for (int k = i+1; k < n; ++k)
      if (fabs(A[k][i]) > fabs(A[iMax][i]))
	iMax = k;
    if (iMax != i) {
      double *tmp, aux;
      tmp = A[i];
      A[i] = A[iMax];
      A[iMax] = tmp;

      aux = b[i]
      b[i] = b[iMax];
      b[iMax] = aux;
    }

    for (int k = i+1; k < n; ++k) {
      double m = A[k][i] / A[i][i];
      A[k][i]  = 0.0;
      for (int j = i+1; j < n; ++j)
	A[k][j] -= A[i][j]*m;
      b[k] -= b[i]*m;
    }
  }
}

void retrossubs(double **A, double *b, double *x, int n) {
  for (int i = n-1; i >= 0; --i) {
    x[i] = b[i];
    for (int j = i+1; j < n; ++j)
      x[i] -= A[i][j]*x[j];
    x[i] /= A[i][i];
  }
}

void resolveSL(double **A, double *b, double *x, int n) {
  eliminacaoGauss(A, b, n);
  retrossubs(A, b, x, n); 
}

void constroiLU (double **A, double **L, double **U, int n){
	if (!A || !L || !U || n <= 0)
		return
	for (int i = 0; i < n; ++i){
		for (int k = 0; k < n; ++k){
			if (k < i){
				L[i][k] = A[i][k] / A[i-1][k];
				U[i][k] = 0;
			}
			else if (k == i){
				L[i][k] = 1;
				U[i][k] = A[i][k];
			}
			else{
				L[i][k] = 0;
				U[i][k] = A[i][k];
			}
		}
	}
}

void L_y_b (double **L, double *y, double *b, int n){
	for (int i = 0; i < n; ++i){
		y[i] = b[i];
                for (int k = 0; k <= i; ++k){
                        y[i] -= L[i][k]*y[k];
                }
        }
}

void U_x_y (double **U, double *x, double *y, int n){
	for (int i = n-1; n >= 0; --n){
                x[i] = y[i];
                for (int k = i+1; k < n; ++k){
                        x[i] -= U[i][k]*x[k];
                }
                x[i] /= U[i][i];
        }

}

void resolveInvert (double **A, double **L, double **U, int n){
	double *x = malloc (sizeof (double)*n);
	double *y = malloc (sizeof (double)*n);
	double *b = calloc (n, sizeof(double));

	for (int i = 0; i < n; ++i){
		b[i] = 1;
		L_y_b (L, y, b, n);
		U_x_y (U, x, y, n);
		for (int k = 0; k < n; ++k)
			A[i][k] = x[k];
		b[i] = 0;
	}

