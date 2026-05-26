#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "broyden.h"
#include "utils.h"

int main() {
    int n = N;
    double *x       = (double *) malloc(n * sizeof(double)); // vetor com as variáveis x
    double *f       = (double *) malloc(n * sizeof(double)); // vetor com cada resultado de f(x)
    double *menos_f = (double *) malloc(n * sizeof(double)); // -F(X)
    double *s       = (double *) malloc(n * sizeof(double)); // delta usado para atualizar x (i+1)
    double *a       = (double *) malloc(n * sizeof(double)); // subdiagonal
    double *b       = (double *) malloc(n * sizeof(double)); // diagonal principal
    double *c       = (double *) malloc(n * sizeof(double)); //

    /* chute inicial classico: todos -1 */
    for (int i = 0; i < n; i++) x[i] = -1.0;

    printf("Newton aplicado ao sistema de Broyden (n = %d)\n", n);
    printf("==============================================\n");
    printf(" k |    ||F(x)||      |    ||s||\n");
    printf("---+------------------+------------------\n");

    for (int k = 0; k < MAX_ITER; k++) {
        avaliaF(x, f, n);
        double nF = norma(f, n);

        if (nF < TOL) {
            printf("%2d | %.6e |  (convergiu)\n", k, nF);
            printf("\nConvergencia em %d iteracoes.\n", k);
            break;
        }

        montaJacobiana(x, a, b, c, n);

        for (int i = 0; i < n; i++) menos_f[i] = -f[i];

        if (thomas(a, b, c, menos_f, s, n) != 0) {
            printf("\nErro: Jacobiana singular na iteracao %d.\n", k);
            return 1;
        }

        for (int i = 0; i < n; i++) x[i] += s[i];

        printf("%2d | %.6e | %.6e\n", k, nF, norma(s, n));

        if (norma(s, n) < TOL) {
            avaliaF(x, f, n);
            printf("\nConvergencia (passo pequeno) em %d iteracoes.\n", k + 1);
            printf("||F(x)|| final = %.3e\n", norma(f, n));
            break;
        }
    }

    printf("\nSolucao aproximada:\n");
    for (int i = 0; i < n; i++)
        printf("  x[%2d] = %.12f\n", i + 1, x[i]);

    free(x); free(f); free(menos_f); free(s);
    free(a); free(b); free(c);
    return 0;
}