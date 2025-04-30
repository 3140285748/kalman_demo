#include "kalman.h"

void kalman_noise(KALMAN_STRUCT* kalman)
{   
    float noise[NUMBER_OF_Z];
    float processed_Z[NUMBER_OF_Z];
    generate_gaussian_array(noise,NUMBER_OF_Z, 0,1);
    matrix_add(1, NUMBER_OF_Z,kalman->TRUE_Z,noise, processed_Z);
    for(int i=0;i<NUMBER_OF_Z;i++)
    {
        kalman->Z[i]=processed_Z[i];
    }
}

float kalman_once(KALMAN_STRUCT* kalman,int i)
{
    float X_[NUMBER_OF_X][1];
    float P_[NUMBER_OF_X][NUMBER_OF_X];
    float K[2][1];
    float I[NUMBER_OF_X][NUMBER_OF_X];
    get_I_matrix((float*)I,NUMBER_OF_X);
    float transH[NUMBER_OF_X][1];
    float transF[NUMBER_OF_X][NUMBER_OF_X];
    float middle_P_[NUMBER_OF_X][NUMBER_OF_X];
    float middle_K[1];
    float middle_k2[2][1];
    float middle_x[1];
    float middle_x2[2][1];
    float middle_t_P[2][2];
    //公式1
    multiply(NUMBER_OF_X,NUMBER_OF_X,1,(float*)kalman->F,(float*)kalman->X,(float*)X_);//X_=F*X
    //公式2
    matrix_ABAT(NUMBER_OF_X,NUMBER_OF_X,(float*)kalman->F,(float*)kalman->P,(float*)middle_P_);
    matrix_add(NUMBER_OF_X, NUMBER_OF_X,(float*)middle_P_,(float*)kalman->Q,(float*)P_);//P_=P+Q;
    //公式3
    transpose(1,NUMBER_OF_X,(float*)kalman->H,(float*)transH);//求H'
    matrix_ABAT(1,NUMBER_OF_X,(float*)kalman->H,(float*)P_,middle_K);//求H*P*H'
    middle_K[0]+=kalman->R;//H*P*H'+R
    middle_K[0]=1/middle_K[0];//求逆
    multiply(NUMBER_OF_X,NUMBER_OF_X,1,(float*)P_,(float*)transH,(float*)middle_k2);//P_*H'
    multiply(NUMBER_OF_X,1,1,(float*)middle_k2,(float*)middle_K,(float*)K);//P_*H'*inv
    //公式4
    multiply(1,NUMBER_OF_X,1,(float*)kalman->H,(float*)X_,(float*)middle_x);//H*X_
    middle_x[0]=kalman->Z[i]-middle_x[0];//z[i]-H*X_
    multiply(NUMBER_OF_X,1,1,(float*)K,(float*)middle_x,(float*)middle_x2);//K*(Z[i]-H*X_)
    matrix_add(2,1,(float*)X_,(float*)middle_x2,(float*)kalman->X);//X_+(K*(Z[i]-H*X_))
    //公式5
    multiply(NUMBER_OF_X,1,NUMBER_OF_X,(float*)K,(float*)kalman->H,(float*)middle_P_);//K*H
    matrix_sub(NUMBER_OF_X,NUMBER_OF_X,(float*)I,(float*)middle_P_,(float*)middle_t_P);//I-K*H
    multiply(NUMBER_OF_X,NUMBER_OF_X,NUMBER_OF_X,(float*)middle_t_P,(float*)P_,(float*)kalman->P);//(I-K*H)*P_

    return pow(kalman->X[0][0]-kalman->Z[i+1],2);
}


void kalman_copy(KALMAN_STRUCT* kalman,KALMAN_STRUCT* kalman_f_count)
{
    matrix_copy(NUMBER_OF_X,NUMBER_OF_X,(float*)kalman->F,(float*)kalman_f_count->F);
    matrix_copy(1,NUMBER_OF_Z,(float*)kalman->TRUE_Z,(float*)kalman_f_count->TRUE_Z);
    matrix_copy(NUMBER_OF_X,1,(float*)kalman->X,(float*)kalman_f_count->X);
    matrix_copy(NUMBER_OF_X,NUMBER_OF_X,(float*)kalman->P,(float*)kalman_f_count->P);
    matrix_copy(NUMBER_OF_X,NUMBER_OF_X,(float*)kalman->Q,(float*)kalman_f_count->Q);
    matrix_copy(1,NUMBER_OF_X,(float*)kalman->H,(float*)kalman_f_count->H);
    kalman_f_count->R=kalman->R;
}


void kalman_find_best_Q(KALMAN_STRUCT* kalman,float* stddev)
{
    KALMAN_STRUCT kalman_f_count;
   
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            kalman_copy((KALMAN_STRUCT*)&kalman,&kalman_f_count);
            kalman_f_count.Q[1][1]=0.1*j+0.0001;
            kalman_f_count.Q[0][0]=0.1*i+0.0001;
            kalman_noise(&kalman_f_count);
            for(int e=0;e<EPOCH-1;e++)
            {
                stddev[i*10+j]+=kalman_once(&kalman_f_count,e);
            }
            stddev[i*10+j]/=EPOCH-1;
        }
    }

}

