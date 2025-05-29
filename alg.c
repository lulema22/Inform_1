#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alg.h"
#include "matrix.h"

LU decomposition(Matrix mat){
    if (strcmp(mat.type, "int") == 0){
        mat = intToFloat(mat);

    }
    LU lu;
    lu.L = create_matrix(mat.size, mat.type);
    lu.U = create_matrix(mat.size, mat.type);


    float **m = (float** )mat.data;
    float **L = (float**) lu.L.data;
    float **U = (float**) lu.U.data;


    for (int i =0; i< mat.size; i++){
        for (int j=0; j< mat.size; j++){
            L[i][j]= 0;
            U[i][j]= 0;
        }
        L[i][i] = 1;
    }
    for (int i = 0; i < mat.size; i++){
        for (int j= 0; j < mat.size; j++){
            if (i==0){
                U[i][j] = m[i][j];
            }
            else if (i != 0.0 && j>=i){
                float sum = 0;
                for (int k= 0; k < i; k++){
                    sum += (L[i][k]* U[k][j]);

                }
                U[i][j] = m[i][j] - sum;
            }
            else {
                float sum = 0;
                for (int k= 0; k < j; k++){
                    sum += (L[i][k]* U[k][j]);

                }
                L[i][j]= (m[i][j] - sum)*1/U[j][j];
            }

        }
    }

    return lu;
}



Matrix inverseMatrix(Matrix mat){
    LU lu = decomposition(mat);
    Matrix U = lu.U;
    Matrix L = lu.L;
    float **l = (float**)L.data;
    float **u = (float**)U.data;
    Matrix U_I = create_matrix(mat.size, "float");
    Matrix L_I = create_matrix(mat.size, "float");
    float **l_i = (float**)L_I.data;
    float **u_i = (float**)U_I.data;


    for (int i =0; i < mat.size; i++){
        for (int j=0; j< mat.size; j++){
            l_i[i][j]= 0;
            u_i[i][j]= 0;
        }
        l_i[i][i] = 1.0;
    }

    for (int i= mat.size - 1; i>= 0; i--){
        for (int j = i; j < mat.size; j++){
            if (i == j){
                u_i[i][j] = 1/u[i][i];

            } else {
                float sum = 0;
                for(int k = i+1; k <=j; k++) {
                    sum += u[i][k] * u_i[k][j];
                }
                u_i[i][j] = -sum/u[i][i];
            }
        }
    }

    for (int i= 1; i < mat.size; i++){
        for (int j = 0; j < i; j++){
            float sum = 0;
            for(int k = j; k <i ; k++) {
                sum += l[i][k] * l_i[k][j];
            }
            l_i[i][j] = -sum;
        }
    }
    Matrix res = multiply_matrices(U_I, L_I);
    free_matrix(U);
    free_matrix(L);
    free_matrix(U_I);
    free_matrix(L_I);

    return res;
}


float deter(Matrix mat){
    LU res = decomposition(mat);
    Matrix matU = res.U;
    float **m = (float**)matU.data;
    float det = m[0][0];
    for (int i = 1; i< matU.size; i++){
        det *= m[i][i];
    }
    return det;

}



float* SLAU(Matrix A, float* B, int Bsize){
    LU lu = decomposition(A);
    Matrix L = lu.L;
    Matrix U = lu.U;
    float *y = malloc(A.size * sizeof(float));
    float *x = malloc(A.size * sizeof(float));



    float **a = (float**)A.data;
    float **l = (float**)L.data;
    float **u = (float**)U.data;
    for (int i = 0; i < A.size; i++){
        float sum = 0.0;
        for (int k = 0; k < i; k++){
            sum += y[k]* l[i][k];
        }
        y[i]= B[i] - sum;

    }
    for (int i = A.size - 1; i >= 0; i--){
        float sum = 0.0;
        for (int k = i+1; k < A.size; k++){
            sum += u[i][k]*x[k];
        }
        x[i] = (y[i] - sum)/u[i][i];
    }
    free(y);
    free_matrix(L);
    free_matrix(U);
    return x;
}






void writeMatrixLU(FILE *file, LU lu){
    fprintf(file, "Matrix L:\n");
    write_matrix(file, lu.L);
    fprintf(file, "\nMatrix U:\n");
    write_matrix(file, lu.U);
}