#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

// real_t: tipo usado para representar valores em ponto flutuante
typedef double real_t;

// string_t: tipo usado para representar ponteiros para char/strings
typedef char * string_t;

// rtime_t: tipo usado para representar valores de tempo em ponto flutuante
typedef double rtime_t;

// lint_t: tipo usado para representar valores long int
typedef long long int lint_t;

// Número máximo de dígitos em um número inteiro
#define numDigits(n)  6

// Funções
rtime_t timestamp(void);
string_t markerName(string_t baseName, int n);

#endif // __UTILS_H__

