#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utils.h"

void constroiLU (double **A, double **L, double **U, int n){
	if (!A || !L || !U || n <= 0)
		return ;

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

void resolveInvert (double **A, double **L, double **U, double **Inv, int n){
	double *x = calloc (n, sizeof (double));
	double *y = calloc (n, sizeof (double));
	double *b = calloc (n, sizeof (double));

	for (int i = 0; i < n; ++i){
		b[i] = 1;
		L_y_b (L, y, b, n);
		U_x_y (U, x, y, n);
		for (int k = 0; k < n; ++k)
			Inv[i][k] = x[k];
		b[i] = 0;
	}

	free (x);
	free (y);
	free (b);
}

void printMatriz (double **A, int n){
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j)
			printf ("%f ", A[i][j]);
		printf ("\n");
	}
}

