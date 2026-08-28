#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

// Retorna valor do erro quando método finalizou. Este valor depende de tipoErro
real_t newtonRaphson (Polinomio p, real_t x0, int criterioParada, int *it, real_t *raiz)
{
	int para, i = 0;
	real_t err;
	real_t px, pdx;
	real_t x_new;

	while (i < MAXIT && !para){
		if (criterioParada == 1){
                        para = fabs (
                }
                else if (criterioParada == 2){

                }
                else{

                }

		calcPolinomio (p, x0, &px, &pdx);
		x_new = x0 - px / pdx;

		err = fabs ((x_new - x0) / x_new) * 100;
		if (err < EPS){
			*raiz = x_new;
			para = 1;
		}
		i++;
	}
	*it = i;

	return err;
}


// Retorna valor do erro quando método finalizou. Este valor depende de tipoErro
real_t bisseccao (Polinomio p, real_t a, real_t b, int criterioParada, int *it, real_t *raiz)
{
	int para, i = 0;
	real_t err;
	real_t xm = (a + b) / 2;
	real_t xm_new;
	real_t px_a, px_xm, dpx;

	while (i < MAXIT && !para){
		// Checa se o criterio de parada foi atendido
		if (criterioParada == 1){
			para = fabs (
		}
		else if (criterioParada == 2){

		}
		else{

		}
		
		calcPolinomio_lento (p, a, &px_a, &dpx);
		calcPolinomio_lento (p, xm, &px_xm, &dpx);

		if (px_a * px_xm < 0){
			b = xm;
		}
		else if (px_a * px_m > 0){
			a = xm;
		}
		else{
			*raiz = xm;
			para = 1;
		}
		
		xm_new = (a + b) / 2;
		err = fabs ((xm_new - xm) / xm_new) * 100;

		if (err <= EPS){
			*raiz = xm;
			para = 1;
		}
		i++;
	}
	*it = i;

	return err;	
}


void calcPolinomio_rapido(Polinomio p, real_t x, real_t *px, real_t *dpx)
{
	for (int i = 0; i < p.grau; ++i){
		
	}
}


void calcPolinomio_lento(Polinomio p, real_t x, real_t *px, real_t *dpx)
{
	real_t *p = p.p;
	for (int i = p.grau; i >= 0; --i){
		*px += p[i] * pow (x,i);
		*dpx += p[i]*i * pow (x,i-1);
	}	
}
