#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

// Retorna valor do erro quando método finalizou. Este valor depende de tipoErro
real_t newtonRaphson (Polinomio* p, real_t x0, int criterioParada, int *it, real_t *raiz)
{
	int para = 0;
	int itera = 0;
	real_t err;
	real_t px, dpx;
	real_t x_new;

	while (itera < MAXIT && !para){
		calcPolinomio_lento (p, x0, &px, &dpx);
		x_new = x0 - px / dpx;

		err = fabs ((x_new - x0) / x_new) * 100;
		if (err < EPS){
			para = 1;
		}

		if (criterioParada == 1){
                        if (fabs ((x_new - x0) / x_new) <= 10e-7)
				para = 1;
                }
                else if (criterioParada == 2){
			calcPolinomio_lento (p, x_new, &px, &dpx);
			if (fabs (px) <= DBL_EPSILON)
				para = 1;
                }
		
		*raiz = x_new;
		x0 = x_new;
		itera++;
		px = 0;
		dpx = 0;

	}
	*it = itera;

	return err;
}

// Retorna valor do erro quando método finalizou. Este valor depende de tipoErro
real_t bisseccao (Polinomio* p, real_t a, real_t b, int criterioParada, int *it, real_t *raiz)
{
	int para, i = 0;
	real_t err;
	real_t xm = (a + b) / 2;
	real_t xm_new;
	real_t px_a, px_xm, dpx;

	while (i < MAXIT && !para){
		
		calcPolinomio_lento (p, a, &px_a, &dpx);
		calcPolinomio_lento (p, xm, &px_xm, &dpx);

		if (px_a * px_xm < 0){
			b = xm;
		}
		else if (px_a * px_xm > 0){
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

		if (criterioParada == 1){
                        para = fabs ((xm_new - xm) / xm_new) <= 10e-7;
                }
                else if (criterioParada == 2){
                        calcPolinomio_lento (p, xm_new, &px_xm, &dpx);
                        para = fabs (px_xm) <= DBL_EPSILON;
                }
                else{
                        printf ("erro!\n");
                }

		px_a = 0;
		px_xm = 0;

	}
	*it = i;

	return err;	
}


void calcPolinomio_rapido(Polinomio p, real_t x, real_t *px, real_t *dpx)
{
	return ;
}


void calcPolinomio_lento(Polinomio* p, real_t x, real_t *px, real_t *dpx)
{
	real_t *poli = p->p;
	for (int i = p->grau; i >= 0; --i){
		*px += poli[i] * pow (x,i);
		*dpx += poli[i]*i * pow (x,i-1);
	}	
}
