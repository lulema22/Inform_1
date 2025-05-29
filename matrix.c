#include "matrix.h"

// --- реализации TypeInfo для int ---
static void intAdd(void* a, void* b, void* result) {
    *((int*)result) = *((int*)a) + *((int*)b);
}
static void intMult(void* a, void* b, void* result) {
    *((int*)result) = *((int*)a) * *((int*)b);
}
static void intScalar(void* a, float scalar, void* result) {
    *((int*)result) = *((int*)a) * (int)scalar;
}
TypeInfo TypeInt = { intAdd, intMult, intScalar, sizeof(int) };

// --- реализации TypeInfo для float ---
static void floatAdd(void* a, void* b, void* result) {
    *((float*)result) = *((float*)a) + *((float*)b);
}
static void floatMultiply(void* a, void* b, void* result) {
    *((float*)result) = *((float*)a) * *((float*)b);
}
static void floatScalar(void* a, float scalar, void* result) {
    *((float*)result) = *((float*)a) * scalar;
}
TypeInfo TypeInfoFloat = { floatAdd, floatMultiply, floatScalar, sizeof(float) };

// --- реализация функций работы с матрицами ---
Matrix create_matrix(int size, const char *type) {
    Matrix mat;
    mat.size = size;
    strcpy(mat.type, type);

    if (strcmp(type, "int") == 0) {
        mat.typeInfo = &TypeInt;
    } else if (strcmp(type, "float") == 0) {
        mat.typeInfo = &TypeInfoFloat;
    } else {
        fprintf(stderr, "неверный тип: %s\n", type);
        exit(EXIT_FAILURE);
    }

    mat.data = malloc(size * sizeof(void*));
    for (int i = 0; i < size; i++)
        mat.data[i] = malloc(size * mat.typeInfo->type_size);

    return mat;
}

void free_matrix(Matrix mat) {
    for (int i = 0; i < mat.size; i++)
        free(mat.data[i]);
    free(mat.data);
}

// Matrix read_matrix(FILE *file) {
//     int size;
//     char type[10];
//     fscanf(file, "%d", &size);
//     fscanf(file, "%s", type);
//     if (strcmp(type, "int") != 0 && strcmp(type, "float") != 0) {
//         fprintf(stderr, "ошибка: %s\n", type);
//         return create_error_matrix("ошибка");
//     }
//     Matrix mat = create_matrix(size, type);
//     if (strcmp(type, "int") == 0) {
//         int **data = (int **)mat.data;
//         for (int i = 0; i < size; i++) {
//             for (int j = 0; j < size; j++) {
//                 fscanf(file, "%d", &data[i][j]);
//             }
//         }
//     } else if (strcmp(type, "float") == 0) {
//         float **data = (float **)mat.data;
//         for (int i = 0; i < size; i++) {
//             for (int j = 0; j < size; j++) {
//                 fscanf(file, "%f", &data[i][j]);
//             }
//         }
//     }
//     return mat;
// }

Matrix create_error_matrix(const char *error_message) {
    Matrix mat;
    mat.size = -1;
    strcpy(mat.type, "error");
    mat.data = NULL;
    fprintf(stderr, "%s\n", error_message);
    return mat;
}

Matrix input_matrix(void) {
    char type[10];
    int size;
    printf("Type (int/float): ");
    scanf("%9s", type);
    printf("Size: ");
    scanf("%d", &size);

    Matrix mat = create_matrix(size, type);
    printf("Enter elements:\n");
    if (strcmp(type, "int") == 0) {
        int **d = (int**)mat.data;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                scanf("%d", &d[i][j]);
    } else {
        float **d = (float**)mat.data;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                scanf("%f", &d[i][j]);
    }
    return mat;
}
// void writeMatrixLU( FILE *file, LU lu){
//     write_matrix(file, lu.L);
//     write_matrix(file, lu.U);
// }

// void writeMatrixLU(FILE *file, LU lu){
//     fprintf(file, "Matrix L:\n");
//     write_matrix(file, lu.L);
//     fprintf(file, "\nMatrix U:\n");
//     write_matrix(file, lu.U);
// }

void write_matrix(FILE *file, Matrix mat) {
    if (mat.size < 0) {
        fprintf(file, "Ошибка: %s\n", mat.type);
        return;
    }
    fprintf(file, "%d %s\n", mat.size, mat.type);
    if (strcmp(mat.type, "int") == 0) {
        int **d = (int**)mat.data;
        for (int i = 0; i < mat.size; i++) {
            for (int j = 0; j < mat.size; j++)
                fprintf(file, "%d ", d[i][j]);
            fprintf(file, "\n");
        }
    } else {
        float **d = (float**)mat.data;
        for (int i = 0; i < mat.size; i++) {
            for (int j = 0; j < mat.size; j++)
                fprintf(file, "%.2f ", d[i][j]);
            fprintf(file, "\n");
        }
    }
}

Matrix transpose_matrix(Matrix mat) {
    Matrix r = create_matrix(mat.size, mat.type);
    if (strcmp(mat.type, "int") == 0) {
        int **a = (int**)mat.data, **b = (int**)r.data;
        for (int i = 0; i < mat.size; i++)
            for (int j = 0; j < mat.size; j++)
                b[j][i] = a[i][j];
    } else {
        float **a = (float**)mat.data, **b = (float**)r.data;
        for (int i = 0; i < mat.size; i++)
            for (int j = 0; j < mat.size; j++)
                b[j][i] = a[i][j];
    }
    return r;
}

Matrix scalarMultiply(Matrix mat, float k) {
    Matrix r = create_matrix(mat.size, mat.type);
    float **a = (float**)mat.data, **b = (float**)r.data;
    for (int i = 0; i < mat.size; i++)
        for (int j = 0; j < mat.size; j++)
            b[i][j] = k * a[i][j];
    return r;
}

Matrix intToFloat(Matrix m) {
    Matrix r = create_matrix(m.size, "float");
    int **a = (int**)m.data; float **b = (float**)r.data;
    for (int i = 0; i < m.size; i++)
        for (int j = 0; j < m.size; j++)
            b[i][j] = (float)a[i][j];
    return r;
}

Matrix add_matrices(Matrix a, Matrix b) {
    if (a.size!=b.size||strcmp(a.type,b.type)!=0) return create_error_matrix("size/type mismatch");
    Matrix r = create_matrix(a.size,a.type);
    for(int i=0;i<a.size;i++)
        for(int j=0;j<a.size;j++)
            a.typeInfo->add((char*)a.data[i]+j*a.typeInfo->type_size,
                            (char*)b.data[i]+j*b.typeInfo->type_size,
                            (char*)r.data[i]+j*r.typeInfo->type_size);
    return r;
}

Matrix multiply_matrices(Matrix a, Matrix b) {
    if (a.size!=b.size||strcmp(a.type,b.type)!=0) return create_error_matrix("size/type mismatch");
    Matrix r = create_matrix(a.size,a.type);
    for(int i=0;i<a.size;i++) for(int j=0;j<a.size;j++){
        // zero
        memset((char*)r.data[i]+j*a.typeInfo->type_size,0,a.typeInfo->type_size);
        for(int k=0;k<a.size;k++){
            void *t1=malloc(a.typeInfo->type_size),
                 *t2=malloc(a.typeInfo->type_size);
            a.typeInfo->mult((char*)a.data[i]+k*a.typeInfo->type_size,
                             (char*)b.data[k]+j*b.typeInfo->type_size,t1);
            a.typeInfo->add((char*)r.data[i]+j*a.typeInfo->type_size,
                            t1,t2);
            memcpy((char*)r.data[i]+j*a.typeInfo->type_size,t2,a.typeInfo->type_size);
            free(t1); free(t2);
        }
    }
    return r;
}


Matrix linear_combination(Matrix mat, int string, float *cf) {
    int row_index = string - 1;

    if (row_index < 0 || row_index >= mat.size) {
        return create_error_matrix("ошибка");
    }
    Matrix result = create_matrix(mat.size, mat.type);

    if (strcmp(mat.type, "int") == 0) {
        for (int i = 0; i < mat.size; i++) {

            for (int j = 0; j < mat.size; j++) {
                ((int **)result.data)[i][j] = ((int **)mat.data)[i][j];
            }
        }

    } else if (strcmp(mat.type, "float") == 0) {
        for (int i = 0; i < mat.size; i++) {
            for (int j = 0; j < mat.size; j++) {

                ((float **)result.data)[i][j] = ((float **)mat.data)[i][j];
            }
        }
    }
    int coeff_index = 0;
    for (int i = 0; i < mat.size; i++) {
        if (i != row_index) {  // Пропускаем
            for (int j = 0; j < mat.size; j++) {
                if (strcmp(mat.type, "int") == 0) {
                    ((int **)result.data)[row_index][j] += (int)(cf[coeff_index] * ((int **)mat.data)[i][j]);

                } else if (strcmp(mat.type, "float") == 0) {
                    ((float **)result.data)[row_index][j] += cf[coeff_index] * ((float **)mat.data)[i][j];
                }
            }
            coeff_index++;  // К следующему коэффициенту
        }
    }

    return result;
}

float* readFloatArray(int *size) {
    char buf[1024];
    float *arr = NULL;
    int count = 0;
    if (fgets(buf, sizeof(buf), stdin) != NULL) {
        char *token = strtok(buf, " \t\n");
        while (token) {
            float *tmp = realloc(arr, (count + 1) * sizeof(float));
            if (!tmp) { free(arr); exit(EXIT_FAILURE); }
            arr = tmp;
            arr[count++] = atof(token);
            token = strtok(NULL, " \t\n");
        }
    }
    *size = count;
    return arr;
}
