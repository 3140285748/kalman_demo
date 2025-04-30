#ifndef _MATRIX_H
#define _MATRIX_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define M_PI 3.14159265358979323846
#define EPSILON 1e-8

void transpose(int rows, int cols, const float* A, float* AT);
void multiply(int m, int n, int p, const float* A, const float* B, float* C);
int inverse(int n, const float* A, float* invA);
int matrix_add(int rows, int cols, const float* A, const float* B, float* C);
void generate_gaussian_array(float* array, int size, float mean, float stddev);
void get_I_matrix(float* I,int i);
void matrix_ABAT(int m ,int n ,float* A,float* B,float* C);
int matrix_sub(int rows, int cols, const float* A, const float* B, float* C);
void matrix_copy(int rows,int cols,float *A,float *B);





#endif