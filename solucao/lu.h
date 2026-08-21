#ifndef __LU_H__
#define __LU_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "utils.h"
#include "matriz.h"

unsigned int *triangLU(Matriz_t A, unsigned int n);
void Ly_b(Matriz_t A, real_t *B, real_t *Y, unsigned int n, unsigned int *trocas);
void Ux_y(Matriz_t A, real_t *Y, real_t *x, unsigned int n);

#endif // __LU_H__

