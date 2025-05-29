#ifndef ALG_H
#define ALG_H

#include "matrix.h"

// Структура для разложения LU
typedef struct {
    Matrix L;
    Matrix U;
} LU;

// Прототипы функций
LU decomposition(Matrix mat);
Matrix inverseMatrix(Matrix mat);
float deter(Matrix mat);
float* SLAU(Matrix A, float* B, int Bsize);
void writeMatrixLU(FILE *file, LU lu);

#endif // ALG_H
