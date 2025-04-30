#include <stdio.h>
#include "matrix.h"

int main() {
    // 测试矩阵转置
    /*float A[2][3] = {{2,3,4}, {4,5,6}};
    float AT[3][2];
    transpose(2, 3, (float*)A,(float*) AT);

    printf("Original Matrix A:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%.2f ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nTransposed Matrix AT:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%.2f ", AT[i][j]);
        }
        printf("\n");
    }*/

    // 测试矩阵乘法
    /*float B[3][2] = {{7, 8}, {9, 10}, {11, 12}};
    float C[2][2];
    multiply(2, 3, 2,(float*) A,(float*) B, (float*)C);

    printf("\nMatrix Multiplication Result C:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%.2f ", C[i][j]);
        }
        printf("\n");
    }*/
        // 测试3x3矩阵
    /*float D[3][3] = {
            {1, 2, 3},
            {0, 1, 4},
            {5, 6, 0}};
    
    float invD[3][3];
    int status = inverse(3, (float*)D, (float*)invD);
    
    if (status != 0) {
        printf("Matrix is singular or error occurred!\n");
        return 1;
    }
    
    printf("Original Matrix D:\n");
    for (int i = 0; i < 3; ++i) {
         for (int j = 0; j < 3; ++j) {
            printf("%8.3f", D[i][j]);
        }
        printf("\n");
    }
    
    printf("\nInverse Matrix invD:\n");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%8.3f", invD[i][j]);
        }
        printf("\n");
    }
*/
    /*float E[3][3];
    matrix_add(3, 3, (float*)D, (float*)invD, (float*)E);
    printf("\n E:\n");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%8.3f", E[i][j]);
        }
        printf("\n");
    }
*/
    /*float G[100];
    generate_gaussian_array((float*)G, 100, 0, 0.5);
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            printf("%8.3f",G[i*10+j]);
        }
        printf("\n");
    }

    float I[3][3];
    get_I_matrix((float *)I,3);
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("%8.3f",I[i][j]);
        }
        printf("\n");
    }*/
   float A[2][3]={{1,2,3},{4,5,6}};
   float B[3][3]={{1,2,3},{3,4,5},{6,7,8}};
   float C[2][2]={0};
   float D[2][3]={0};
   matrix_ABAT(2,3,(float*)A,(float*)B,(float*)C);
   for(int i=0;i<2;i++)
   {
    for(int j=0;j<2;j++)
    {
        printf("%8.2f",C[i][j]);
    }
    printf("\n");
   }
   matrix_copy(2,3,(float*)A,(float*)D);
   for(int i=0;i<2;i++)
   {
    for(int j=0;j<3;j++)
    {
        printf("%8.2f",D[i][j]);
    }
    printf("\n");
   }
   float Z[20];
   for(int i=0;i<20;i++)
   {
       Z[i]=(float)i;
       printf("%.2f",Z[i]);
   }
   
    return 0;
}
