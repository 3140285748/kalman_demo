#include "kalman.h"

int main()
{
    KALMAN_STRUCT my_kalman;
    float Z[20]={0};
    for(int i=0;i<20;i++)
    {
        Z[i]=(float)i;
    }
    float X[2][1]={{0},{0}};
    float P[2][2]={{1,0},{0,1}};
    float F[2][2]={{1,1},{0,1}};
    float Q[2][2]={{0.0001,0},{0,0.0001}};
    float H[1][2]={{1,0}};
    float R=1;

    matrix_copy(NUMBER_OF_X,NUMBER_OF_X,(float*)F,(float*)my_kalman.F);
    matrix_copy(1,NUMBER_OF_Z,Z,my_kalman.TRUE_Z);
    matrix_copy(NUMBER_OF_X,1,(float*)X,(float*)my_kalman.X);
    matrix_copy(NUMBER_OF_X,NUMBER_OF_X,(float*)P,(float*)my_kalman.P);
    matrix_copy(NUMBER_OF_X,NUMBER_OF_X,(float*)Q,(float*)my_kalman.Q);
    matrix_copy(1,NUMBER_OF_X,(float*)H,(float*)my_kalman.H);
    my_kalman.R=R;


    float stddev[100]={0};
    //kalman_find_best_Q(&my_kalman,(float*)stddev);
    KALMAN_STRUCT kalman_f_count;
   
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            kalman_copy(&my_kalman,&kalman_f_count);
            kalman_f_count.Q[1][1]=step_of_Q00*j+0.0001;
            kalman_f_count.Q[0][0]=step_of_Q11*i+0.0001;
            kalman_noise(&kalman_f_count);
            for(int e=0;e<EPOCH-1;e++)
            {
                stddev[i*10+j]+=kalman_once(&kalman_f_count,e);
            }
            stddev[i*10+j]/=EPOCH-1;
        }
    }
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            printf("%8.3f\0",stddev[i*10+j]);
        }
        printf("\n");
    }
    float min_stddev;
    int idx;
    find_min(stddev,100,&min_stddev,&idx);
    printf("min_stddev:%8.3f\n",min_stddev);
    printf("Q:[%.2f 0]\n",(idx%10)*step_of_Q00);
    printf("  [0 %.2f]\n",(idx/10)*step_of_Q11);
   /*kalman_noise(&my_kalman);
   float stddev={0};
    for(int i=0;i<20;i++)
    {
        printf("%.2f\n",kalman_once(&my_kalman,i));
        stddev+=kalman_once(&my_kalman,i);
    }
    stddev/=20;
    printf("%.2f",stddev);*/

    return 0;
}


int find_min(const float* arr, int len, float* min_val, int* min_idx) {
    // 参数有效性检查
    if (arr == NULL || min_val == NULL || min_idx == NULL || len <= 0) {
        return -1; // 错误返回
    }

    // 初始化最小值为第一个元素
    *min_val = arr[0];
    *min_idx = 0;

    // 遍历数组寻找最小值
    for (int i = 1; i < len; ++i) {
        if (arr[i] < *min_val) { // 发现更小的值
            *min_val = arr[i];
            *min_idx = i;
        }
    }
    return 0; // 成功返回
}