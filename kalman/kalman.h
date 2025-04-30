#ifndef _KALMAN_H
#define _KALMAN_H
#include "matrix.h"

#define NUMBER_OF_Z 20
#define NUMBER_OF_X 2
#define EPOCH 20
#define step_of_Q00 0.1
#define step_of_Q11 0.13
typedef struct kalman
{
float Z[NUMBER_OF_Z];
float TRUE_Z[NUMBER_OF_Z];
float X[NUMBER_OF_X][1];
float P[NUMBER_OF_X][NUMBER_OF_X];
float F[NUMBER_OF_X][NUMBER_OF_X];
float Q[NUMBER_OF_X][NUMBER_OF_X];
float H[1][NUMBER_OF_X];
float R;
}KALMAN_STRUCT;
void kalman_noise(KALMAN_STRUCT* kalman);
float kalman_once(KALMAN_STRUCT* kalman,int i);
void kalman_find_best_Q(KALMAN_STRUCT* kalman,float* stddev);
void kalman_copy(KALMAN_STRUCT* kalman,KALMAN_STRUCT* kalman_f_count);


#endif