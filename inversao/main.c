#include <stdio.h>
#include <stdlib.h>

#include "linear.h"
#include "utils.h"

int main (){
	int n;
	scanf ("%d", &n);

	double **A, **L, **U, **Inv;
	A = malloc (n * sizeof(double*));
	A[0] = calloc (n, sizeof(double));

	L = calloc (n, sizeof(double*));
	L[0] = calloc (n, sizeof(double));

	U = calloc (n, sizeof(double*));
        U[0] = calloc (n, sizeof(double));

	Inv = calloc (n, sizeof(double*));
        Inv[0] = calloc (n, sizeof(double));

	for (int i = 1; i < n; ++i){
		A[i] = A[0] + i * n;
		L[i] = L[0] + i * n;
		U[i] = U[0] + i * n;
	}

	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j)
			scanf ("%le", &A[i][j]);
	}
	
	printf ("Matriz Inicial:\n");
	printMatriz (A, n);
	

	resolveInvert (A, L, U, Inv, n);
	
	printf ("Matriz, Inversa: \n");
	printMatriz (Inv, n);

	free(A[0]);
	free(L[0]);
	free(U[0]);
	free(A);
	free(L);
	free(U);

	return 0;
}
