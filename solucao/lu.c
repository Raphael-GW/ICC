#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "matriz.h"
#include "lu.h"


// Pivoteamento da Fatoração LU.
// 'trocas[]' é o vetor de índices da ordem atual de linhas da matriz A
static void pivotLU(Matriz_t A, unsigned int i,
		    unsigned int n, unsigned int *trocas)
{
  real_t max = fabs(A[i][i]);
  int max_i = i;
  for (int j = i+1; j < n; ++j) {
    real_t v = fabs(A[j][i]);
    if (v > max) {
      max = v;
      max_i = j;
    }
  }
  if (max_i != i) {
    real_t *tmp = A[i];
    A[i] = A[max_i];
    A[max_i] = tmp;

    int aux = trocas[i];
    trocas[i] = trocas[max_i];
    trocas[max_i] = aux;
  }
}

// Devolve matriz U na triangular superior de A
// Devolve matriz L na triangular estritamente inferior de A
// Retorna pelo vetor 'trocas[]' as trocas de linhas durante pivoteamento.
unsigned int *triangLU(Matriz_t A, unsigned int n)
{
  unsigned int *trocas = (unsigned int *) malloc( sizeof(int) * n );
  for (int i = 0; i < n; ++i)
    trocas[i] = i;

  for (int i = 0; i < n; ++i) {
    
    pivotLU(A, i, n, trocas);
    
    for (int k = i+1; k < n; ++k) {
      real_t m = A[k][i] / A[i][i];
      A[k][i] = m; // Armazena a matriz L na triangular estritamente inferior da matriz A
      for (int j = i+1; j < n; ++j)
	A[k][j] -= A[i][j]*m;
    }
  }

  return trocas;
}

// A matriz L está na triangular estritamente iferior de A
void Ly_b(Matriz_t A, real_t *B, real_t *Y, unsigned int n, unsigned int *trocas)
{
  for (int i = 0; i < n; ++i) {
    Y[i] = B[ trocas[i] ];
    for (int j = 0; j < i; ++j)
      Y[i] -= A[i][j]*Y[j];
    // Y[i] /= A[i][i];
  }
}

// A matriz U está na triangular superior de A
void Ux_y(Matriz_t A, real_t *y, real_t *x, unsigned int n)
{
  for (int i = n-1; i >= 0; --i) {
    x[i] = y[i];
    for (int j = i+1; j < n; ++j)
      x[i] -= A[i][j]*x[j];
    x[i] /= A[i][i];
  }
}

