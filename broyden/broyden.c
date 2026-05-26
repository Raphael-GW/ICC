/*
 * Metodo de Newton aplicado ao Sistema Tridiagonal de Broyden
 * -----------------------------------------------------------
 * Resolve F(x) = 0, onde:
 *   f_1(x) = -2*x_1^2 + 3*x_1 - 2*x_2 + 1
 *   f_i(x) = -2*x_i^2 + 3*x_i - x_{i-1} - 2*x_{i+1} + 1,   2 <= i <= n-1
 *   f_n(x) = -2*x_n^2 + 3*x_n - x_{n-1}
 *
 * A Jacobiana e' tridiagonal:
 *   subdiagonal: a_i = -1                        (i = 2,...,n)
 *   diagonal  : b_i = -4*x_i + 3                 (i = 1,...,n)
 *   superdiag.: c_i = -2                         (i = 1,...,n-1)
 *
 * O sistema linear interno e' resolvido pelo algoritmo de Thomas - O(n).
 *
 * Compilar:  gcc newton_broyden.c -o newton_broyden -lm
 * Executar:  ./newton_broyden
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10            /* dimensao do sistema (mude livremente) */
#define MAX_ITER 50
#define TOL 1e-12

/* --------- F(x): calcula o vetor F no ponto x --------- */
void avaliaF(const double *x, double *f, int n) {
    f[0] = -2.0*x[0]*x[0] + 3.0*x[0] - 2.0*x[1] + 1.0;
    for (int i = 1; i < n - 1; i++) {
        f[i] = -2.0*x[i]*x[i] + 3.0*x[i] - x[i-1] - 2.0*x[i+1] + 1.0;
    }
    /* ultima equacao - conforme o enunciado, sem o +1 */
    f[n-1] = -2.0*x[n-1]*x[n-1] + 3.0*x[n-1] - x[n-2];
}

/* --------- Monta as 3 diagonais da Jacobiana J(x) ---------
 * a: subdiagonal  (indices 1..n-1 usados; a[0] ignorado)
 * b: diagonal     (indices 0..n-1)
 * c: superdiag.   (indices 0..n-2 usados; c[n-1] ignorado)
 */
void montaJacobiana(const double *x,
                    double *a, double *b, double *c, int n) {
    for (int i = 0; i < n; i++) {
        b[i] = -4.0 * x[i] + 3.0;     /* diagonal principal varia com x */
    }
    for (int i = 1; i < n; i++)   a[i] = -1.0;
    for (int i = 0; i < n-1; i++) c[i] = -2.0;
}

/* --------- Algoritmo de Thomas ---------
 * Resolve um sistema tridiagonal A*s = d.
 * Usa vetores auxiliares cl e dl (nao destroi a, b, c, d).
 * Retorna 0 em sucesso, -1 se encontrar pivo nulo.
 */
int thomas(const double *a, const double *b, const double *c,
           const double *d, double *s, int n) {
    double *cl = (double *) malloc(n * sizeof(double));
    double *dl = (double *) malloc(n * sizeof(double));
    if (!cl || !dl) { free(cl); free(dl); return -1; }

    /* varredura para frente */
    if (fabs(b[0]) < 1e-14) { free(cl); free(dl); return -1; }
    cl[0] = c[0] / b[0];
    dl[0] = d[0] / b[0];

    for (int i = 1; i < n; i++) {
        double m = b[i] - a[i] * cl[i-1];
        if (fabs(m) < 1e-14) { free(cl); free(dl); return -1; }
        cl[i] = (i < n-1) ? c[i] / m : 0.0;
        dl[i] = (d[i] - a[i] * dl[i-1]) / m;
    }

    /* substituicao regressiva */
    s[n-1] = dl[n-1];
    for (int i = n - 2; i >= 0; i--)
        s[i] = dl[i] - cl[i] * s[i+1];

    free(cl); free(dl);
    return 0;
}

/* --------- norma euclidiana --------- */
double norma(const double *v, int n) {
    double s = 0.0;
    for (int i = 0; i < n; i++) s += v[i] * v[i];
    return sqrt(s);
}
