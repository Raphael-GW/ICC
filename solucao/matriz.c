/*******************
  Sistemas Lineares 
********************/

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "matriz.h"

// cria um SistLinear_t *SL := (Ax = b) de dimensão n
Matriz_t criaMatriz(unsigned int n)
{

  Matriz_t A;
  
  // Cria Matriz quadrada A de dimensão n
  A = (real_t **) calloc(n, sizeof(real_t *));
    
  if(A) {
    A[0] = (real_t *) calloc( n * n, sizeof(real_t) );
    
    if(A[0]) {
      for (int i=1; i < n; ++i)
	A[i] = A[i-1] + n;
    }
    else {
      free(A);
      A = NULL;
    }
  }
  
  return A;
}

void liberaMatriz(Matriz_t A, real_t *Aini)
{
    if (A) {
      if(Aini)
	free(Aini);
      free(A);
    }
    
}


void lerMatriz (Matriz_t A, unsigned int n)
{

  // printf ("Digite matriz:\n");
  for(int i=0; i < n; ++i) {
    for(int j=0; j < n; ++j)
      scanf ("%lg", A[i]+j);
  }

}

void prnMatriz (Matriz_t A, unsigned int n)
{

  for(int i=0; i < n; ++i) {
    for(int j=0; j < n; ++j)
      printf ("%lg ", A[i][j]);
    
    printf ("\n");
  }

}


void transporMatriz (Matriz_t A, unsigned int n)
{
  real_t aux;
  
  for(int i=0; i < n; ++i)
    for(int j=i+1; j < n; ++j) {
      aux = A[i][j] ;
      A[i][j] = A[j][i];
      A[j][i] = aux;
    }
}

Matriz_t multMatriz (Matriz_t A, Matriz_t B, unsigned int n)
{
  Matriz_t prod = criaMatriz(n);

  if (prod)
    /* Efetua a multiplicação */
    for (int i=0; i < n; ++i)
      for (int j=0; j < n; ++j)
	for (int k=0; k < n; ++k)
	  prod[i][j] += A[i][k] * B[k][j];
  
  return prod;
}


Matriz_t dupMatriz (Matriz_t A, unsigned int n)
{
  Matriz_t dup = criaMatriz(n);

  if (dup)
    for (int i=0; i < n; ++i)
      for (int j=0; j < n; ++j)
	dup[i][j] = A[i][j];
  
  return dup;
}

