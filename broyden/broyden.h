#ifndef __BROYDEN_H__
#define __BROYDEN_H__

void montaJacobiana(const double *x, double *a, double *b, double *c, int n);

void avaliaF(const double *x, double *f, int n);

int thomas(const double *a, const double *b, const double *c, const double *d, double *s, int n);

double norma(const double *v, int n);

#endif