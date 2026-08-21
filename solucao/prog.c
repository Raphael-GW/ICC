#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "matriz.h"
#include "lu.h"

int main() {

  unsigned int n, *trocas;
  real_t aux, *B, *Y, *A0;
  Matriz_t A, InvA, Aini;

  scanf("%d",&n);

  Y = (real_t *) malloc( sizeof(real_t) * n );

  // Cria Matriz InvA de dimensão n
  InvA = criaMatriz(n);
  
  // Cria Coluna de Matriz Identidade de dimensão n
  B = (real_t *) calloc( n, sizeof(real_t) );

  // Cria e lê matriz A que se deseja inverter
  A = criaMatriz(n);
  lerMatriz(A, n);
  Aini = dupMatriz(A, n);
  A0 = A[0];
  
  // Fatoração LU
  trocas = triangLU(A, n);

  // Cálculo da matriz inversa de A --> InvA
  for (int i = 0; i < n; ++i) {
    B[i] = 1.0;
    Ly_b(A, B, Y, n, trocas);
    Ux_y(A, Y, InvA[i], n);
    B[i] = 0.0;
  }

  // Transpor InvA[][]
  transporMatriz(InvA, n);
  
  // Imprime InvA[][]
  printf ("\n");
  prnMatriz(InvA, n);
  printf ("\n");

  /*
  // Verificação
  Matriz_t res = multMatriz (Aini, InvA, n);
  printf ("\n");
  prnMatriz(res, n);
  printf ("\n");

  liberaMatriz(res, res[0]);
  */
  
  liberaMatriz(A, A0);
  liberaMatriz(Aini, Aini[0]);
  liberaMatriz(InvA, InvA[0]);
  free(trocas);
  free(Y);
  free(B);

  return 0;
}

