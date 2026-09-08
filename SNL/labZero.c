#include <stdio.h>
#include <math.h>
#include <float.h>

#include "utils.h"
#include "ZeroFuncao.h"

int main ()
{

  real_t a, b, err;
  Polinomio pol;
  rtime_t Tnewton, Tbissec;
  double raiz;
  int it;

  scanf("%d", &pol.grau);

  for (int i=pol.grau; i >=0; --i)
    scanf("%lf", &pol.p[i]);

  scanf("%lf %lf", &a, &b); // intervalo onde está uma das raizes.
  

  // Restante do programa a partir daqui
  
  Tnewton = timestamp ();
  err = newtonRaphson (pol, (a+b)/2, 1, &it, &raiz);
  Tnewton = timestamp () - Tnewton;

  printf ("Newton    ");
  printf ("%.15e  %.15e  %d  %.8e\n", raiz, err, it, Tnewton); 

  Tnewton = timestamp ();
  err = newtonRaphson (pol, (a+b)/2, 2, &it, &raiz);
  Tnewton = timestamp () - Tnewton;

  printf ("Newton    ");
  printf ("%.15e  %.15e  %d  %.8e\n", raiz, err, it, Tnewton);

  return 0;
}

