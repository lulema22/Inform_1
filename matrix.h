#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

// =========== Типы и структуры ===========

// Описание операций над одним элементом
typedef struct {
    void (*add)(void* a, void* b, void* result);
    void (*mult)(void* a, void* b, void* result);
    void (*scalar)(void* a, float scalar, void* result);
    size_t type_size;
} TypeInfo;

// Экземпляры для int и float
extern TypeInfo TypeInt;
extern TypeInfo TypeInfoFloat;

// Описание матрицы
typedef struct {
    int size;
    char type[10];
    void **data;          // указатели на строки
    TypeInfo *typeInfo;   // какой TypeInfo применять
} Matrix;

// =========== Прототипы функций ===========

// создание / удаление
Matrix create_matrix(int size, const char *type);
void free_matrix(Matrix mat);
Matrix create_error_matrix(const char *error_message);

// ввод / вывод
Matrix input_matrix(void);
void write_matrix(FILE *file, Matrix mat);

// операции
Matrix transpose_matrix(Matrix mat);
Matrix scalarMultiply(Matrix mat, float k);
Matrix add_matrices(Matrix a, Matrix b);
Matrix multiply_matrices(Matrix a, Matrix b);
Matrix intToFloat(Matrix intMat);
Matrix linear_combination(Matrix mat, int row, float *coeffs);
float* readFloatArray(int *size);

#endif // MATRIX_H
