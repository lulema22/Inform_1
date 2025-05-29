#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "alg.h"


int main() {
     int op;
     printf("Select operation:\n");
     printf("1. LU \n");
     printf("2. Matrix addition\n");
     printf("3. Matrix Multuplucation\n");
     printf("4. Matrix transpose\n");
     printf("5. Matrix scalar multiplication\n");
     printf("6. Determinant\n");
     printf("7. Matrix inverse\n");
     printf("8. SLAU\n");
     printf("Enter number: ");
     scanf("%d", &op);

     Matrix mat1, mat2, result;
     LU luRes;
     float det;
     float scalar;
     switch (op) {
         case 1:
             // LU разложение
             printf("Enter matrix for LU:\n");
             mat1 = input_matrix();
             luRes = decomposition(mat1);
             printf("\nAnswer LU:\n");
             writeMatrixLU(stdout, luRes);
             free_matrix(mat1);
             free_matrix(luRes.L);
             free_matrix(luRes.U);
             break;
         case 2:
             // Сложение матриц
             printf("Enter the first matrix:\n");
             mat1 = input_matrix();
             printf("Enter thr second matrix:\n");
             mat2 = input_matrix();
             result = add_matrices(mat1, mat2);
             printf("\nAnswer addition:\n");
             write_matrix(stdout, result);
             free_matrix(mat1);
             free_matrix(mat2);
             free_matrix(result);
             break;
         case 3:
             // Умножение матриц
             printf("Enter the first matrix:\n");
             mat1 = input_matrix();
             printf("Enter the second matrix:\n");
             mat2 = input_matrix();
             result = multiply_matrices(mat1, mat2);
             printf("\nAnswer multiplication:\n");
             write_matrix(stdout, result);
             free_matrix(mat1);
             free_matrix(mat2);
             free_matrix(result);
             break;
         case 4:
             // Транспонирование
             printf("Enter matrix:\n");
             mat1 = input_matrix();
             result = transpose_matrix(mat1);
             printf("\nAnswer transpose:\n");
             write_matrix(stdout, result);
             free_matrix(mat1);
             free_matrix(result);
             break;
         case 5:
             // Скаляное
             printf("Enter matrix:\n");
             mat1 = input_matrix();
             printf("Enter scalar ");
             scanf("%f", &scalar);
             result = scalarMultiply(mat1, scalar);
             printf("\nAnswer:\n");
             write_matrix(stdout, result);
             free_matrix(mat1);
             free_matrix(result);
             break;
         case 6:
             //Детерминант
             printf("Enter Matrix:\n");
             mat1 = input_matrix();
             det = deter(mat1);
             printf("Answer:\n");
             printf("%f", det);
             free_matrix(mat1);
             break;
         case 7:
             // Обратная матрица
             printf("Enter Matrix:\n");
             mat1 = input_matrix();
             result = inverseMatrix(mat1);
             printf("Answer:\n");
             write_matrix(stdout, result);
             free_matrix(mat1);
             free_matrix(result);
             break;
         case 8:
             // Решение СЛАУ
             printf("Enter Matrix:\n");
             mat1 = input_matrix();
             printf("Enter vector:\n");
             int c;
             while ((c = getchar()) != '\n' && c != EOF) { }
             int vecSize;
             float* B = readFloatArray(&vecSize);
             float* x = SLAU(mat1, B, mat1.size);
             for (int i = 0; i < mat1.size; i++) {
                 printf("%.4f ", x[i]);
             }
             printf("\n");
             free(B);
             free(x);
             free_matrix(mat1);
             break;
         default:
             printf("Error\n");
             break;
     }
     return 0;
 }


// int main() {
//     FILE *input_file1 = fopen("input1.txt", "r");
//     FILE *input_file2 = fopen("input2.txt", "r");
//     FILE *output_file = fopen("output.txt", "w");
//     if (!input_file1 || !input_file2 || !output_file) {
//         perror("ошибка");
//         return EXIT_FAILURE;
//     }
//     Matrix mat1 = read_matrix(input_file1);
//     Matrix mat2 = read_matrix(input_file2);
//     LU luMatr = decomposition(mat1);
//     float determ = deter(mat1);
// Matrix SkalarM = scalarMultyply(mat2, 4.4);
// Matrix transposed1 = transpose_matrix(mat1);
// Matrix transposed2 = transpose_matrix(mat2);
// Matrix sum = add_matrices(mat1, mat2);
// Matrix product = multiply_matrices(mat1, mat2);
// int target_row;
// float coefficients[mat1.size - 1];
// fscanf(input_file1, "%d", &target_row);
// for (int i = 0; i < mat1.size - 1; i++) {
//     fscanf(input_file1, "%f", &coefficients[i]);
// }
// // Matrix lin_comb = linear_combination(mat1, target_row, coefficients);
// writeMatriwLU(output_file, luMatr);
// fprintf(output_file, "%f\n", determ);
// write_matrix(output_file, SkalarM);
// write_matrix(output_file, transposed1);
// write_matrix(output_file, transposed2);
// write_matrix(output_file, sum);
// write_matrix(output_file, product);
// write_matrix(output_file, lin_comb);
// free_matrix(mat1);
// free_matrix(mat2);
// free_matrix(transposed1);
// free_matrix(transposed2);
// free_matrix(sum);
// free_matrix(product);
// free_matrix(lin_comb);
//free_matrix(ScalarM);
//free_matrix(luMatr.L);
// free_matrix(luMatr.U);
//     fclose(input_file1);
//     fclose(input_file2);
//     fclose(output_file);
//     return 0;
// }