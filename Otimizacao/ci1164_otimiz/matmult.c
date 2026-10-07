#include <stdio.h>
#include <stdlib.h>    /* exit, malloc, calloc, etc. */
#include <string.h>
#include <getopt.h>    /* getopt */
#include <time.h>
#include <likwid.h>

#include "utils.h"
#include "matriz.h"

/**
 * Exibe mensagem de erro indicando forma de uso do programa e termina
 * o programa.
 */

static void usage(char *progname)
{
  fprintf(stderr, "Forma de uso: %s [ <ordem> ] \n", progname);
  exit(1);
}



/**
 * Programa principal
 * Forma de uso: matmult [ -n <ordem> ]
 * -n <ordem>: ordem da matriz quadrada e dos vetores
 *
 */

int main (int argc, char *argv[]) 
{
  int n=DEF_SIZE;
  
  MatRow mRow_1, mRow_2, resMat;
  Vetor vet, res;
  
  /* =============== TRATAMENTO DE LINHA DE COMANDO =============== */

  if (argc < 2)
    usage(argv[0]);

  n = atoi(argv[1]);
  
  /* ================ FIM DO TRATAMENTO DE LINHA DE COMANDO ========= */
 
  srandom(20262);
      
  res = geraVetor (n, 0); // (real_t *) malloc (n*sizeof(real_t));
  resMat = geraMatRow(n, n, 1);
    
  mRow_1 = geraMatRow (n, n, 0);
  mRow_2 = geraMatRow (n, n, 0);

  vet = geraVetor (n, 0);

  if (!res || !resMat || !mRow_1 || !mRow_2 || !vet) {
    fprintf(stderr, "Falha em alocação de memória !!\n");
    liberaVetor ((void*) mRow_1);
    liberaVetor ((void*) mRow_2);
    liberaVetor ((void*) resMat);
    liberaVetor ((void*) vet);
    liberaVetor ((void*) res);
    exit(2);
  }
    
#ifdef _DEBUG_
    prnMat (mRow_1, n, n);
    prnMat (mRow_2, n, n);
    prnVetor (vet, n);
    printf ("=================================\n\n");
#endif /* _DEBUG_ */
  rtime_t matVet_time, matMat_time, matVetOt_time, matMatOt_time;
  string_t marker;
  LIKWID_MARKER_INIT;

  // Multiplicação SEM Otimizações

  marker = markerName ("MatVet", n);
  LIKWID_MARKER_START (marker);

  matVet_time = timestamp();
  multMatVet (mRow_1, vet, n, n, res);
  matVet_time = timestamp() - matVet_time;

  LIKWID_MARKER_STOP (marker);
  free (marker);
    

  marker = markerName ("MatMat", n);
  LIKWID_MARKER_START (marker);

  matMat_time = timestamp ();
  multMatMat (mRow_1, mRow_2, n, resMat);
  matMat_time = timestamp () - matMat_time;

  LIKWID_MARKER_STOP (marker);
  free(marker);

  // Multiplicação COM Otimizações


  marker = markerName ("MatVet_Otim", n);
  LIKWID_MARKER_START (marker);

  matVetOt_time = timestamp();
  MatVet_Otim (mRow_1, vet, n, n, res);
  matVetOt_time = timestamp() - matVetOt_time;

  LIKWID_MARKER_STOP (marker);
  free (marker);


  marker = markerName("MatMat_Otim", n);
  LIKWID_MARKER_START (marker);

  matMatOt_time = timestamp ();
  MatMat_Otim (mRow_1, mRow_2, n, resMat);
  matMatOt_time = timestamp () - matMatOt_time;

  LIKWID_MARKER_STOP (marker);
  free (marker);
  
  LIKWID_MARKER_CLOSE;
#ifdef _DEBUG_
    prnVetor (res, n);
    prnMat (resMat, n, n);
    printf ("TEMPO MATVET:   %.6f\n", matVet_time);
    printf ("TEMPO MATMAT:   %.6f\n", matMat_time);
    printf ("TEMPO MATVET_OTIM:   %.6f\n", matVetOt_time);
    printf ("TEMPO MATMAT_OTIM:   %.6f\n", matMatOt_time);
#endif /* _DEBUG_ */

  liberaVetor ((void*) mRow_1);
  liberaVetor ((void*) mRow_2);
  liberaVetor ((void*) resMat);
  liberaVetor ((void*) vet);
  liberaVetor ((void*) res);

  return 0;

}

