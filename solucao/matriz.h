/*******************
  Sistemas Lineares 
********************/

#ifndef __MATRIZ__
#define __MATRIZ__

#include "utils.h"

typedef real_t ** Matriz_t;

// cria um SistLinear_t *SL := (Ax = b) de dimensão n
Matriz_t criaMatriz(unsigned int n);

void liberaMatriz(Matriz_t A, real_t *A0);

void lerMatriz (Matriz_t A, unsigned int n);

void prnMatriz (Matriz_t A, unsigned int n);

void transporMatriz (Matriz_t A, unsigned int n);

Matriz_t multMatriz (Matriz_t A, Matriz_t B, unsigned int n);

Matriz_t dupMatriz (Matriz_t A, unsigned int n);

#endif
