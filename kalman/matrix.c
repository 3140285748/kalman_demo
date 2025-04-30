#include "matrix.h"
#include <math.h>
void transpose(int rows, int cols, const float* A, float* AT) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            /* 将A[i][j]的值存入AT[j][i]的位置 */
            AT[j * rows + i] = A[i * cols + j];
        }
    }
}

void multiply(int m, int n, int p, const float* A, const float* B, float* C) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            C[i * p + j] = 0;  // 初始化结果矩阵元素
            for (int k = 0; k < n; ++k) {
                /* C[i][j] += A[i][k] * B[k][j] */
                C[i * p + j] += A[i * n + k] * B[k * p + j];
            }
        }
    }
}

// 0成功，-1矩阵不可逆，-2内存错误
int inverse(int n, const float* A, float* invA) {
    // 输入校验
    if (n < 1 || A == NULL || invA == NULL) return -1;

    // 创建增广矩阵 [A|I]
   float* aug = (float*)malloc(n * 2 * n * sizeof(float));
    if (!aug) return -2;

    // 初始化增广矩阵
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            aug[i * 2*n + j] = A[i * n + j];
            aug[i * 2*n + n + j] = (i == j) ? 1.0 : 0.0;
        }
    }
    // 高斯-约旦消元
    for (int k = 0; k < n; ++k) {
        // 寻找主元（列选主元）
        int max_row = k;
        for (int i = k + 1; i < n; ++i) {
            if (fabs(aug[i * 2*n + k]) > fabs(aug[max_row * 2*n + k])) {
                max_row = i;
            }
        }
        // 奇异矩阵检测
        if (fabs(aug[max_row * 2*n + k]) < EPSILON) {
            free(aug);
            return -1;
        }
        // 交换行
        if (max_row != k) {
            for (int j = 0; j < 2*n; ++j) {
                double tmp = aug[k * 2*n + j];
                aug[k * 2*n + j] = aug[max_row * 2*n + j];
                aug[max_row * 2*n + j] = tmp;
            }
        }
        // 归一化主元行
        double pivot = aug[k * 2*n + k];
        for (int j = 0; j < 2*n; ++j) {
            aug[k * 2*n + j] /= pivot;
        }
        // 消元其他行
        for (int i = 0; i < n; ++i) {
            if (i == k) continue;
            double factor = aug[i * 2*n + k];
            for (int j = 0; j < 2*n; ++j) {
                aug[i * 2*n + j] -= factor * aug[k * 2*n + j];
            }
        }
    }
    // 提取逆矩阵
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            invA[i * n + j] = aug[i * 2*n + n + j];
        }
    }

    free(aug);
    return 0;
}

// 0成功，-1参数错误，-2维度不匹配
int matrix_add(int rows, int cols, const float* A, const float* B, float* C) {
// 参数有效性检查
if (rows <= 0 || cols <= 0) return -1;
if (A == NULL || B == NULL || C == NULL) return -1;

// 执行加法运算
for (int i = 0; i < rows; ++i) {
for (int j = 0; j < cols; ++j) {
  const int index = i * cols + j;
  C[index] = A[index] + B[index];
}
}
return 0;
}


void generate_gaussian_array(float* array, int size, float mean, float stddev) {
    // 初始化随机种子
    srand(time(NULL));
    
    // Box-Muller变换核心逻辑
    for (int i = 0; i < size; ) {
        float u1 = rand() / (RAND_MAX + 1.0);  // [0,1)均匀分布
        float u2 = rand() / (RAND_MAX + 1.0);
        
        // 生成两个独立的高斯随机数
        float z0 = sqrt(-2 * log(u1)) * cos(2 *M_PI * u2);
        float z1 = sqrt(-2 * log(u1)) * sin(2 *M_PI * u2);
        
        // 调整均值和标准差
        array[i++] = z0 * stddev + mean;
        if (i < size) {
            array[i++] = z1 * stddev + mean;
        }
    }
}

void get_I_matrix(float *I,int size)
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            if(j==i)
            {
                I[i*3+j]=1;
            }
            else
                I[i*3+j]=0;
        }
    }
}

void matrix_ABAT(int m ,int n,float* A,float* B,float* C)
{
    float AT[n][m];
    float AB[m][n];
    multiply(m,n,n,A,B,(float*)AB);
    transpose(m,n,A,(float*)AT);
    multiply(m,n,m,(float*)AB,(float*)AT,C);

}

int matrix_sub(int rows, int cols, 
    const float* A, const float* B, 
    float* C) {
// 参数有效性检查
if (rows <= 0 || cols <= 0) return -1;
if (A == NULL || B == NULL || C == NULL) return -1;

// 执行减法运算
for (int i = 0; i < rows; ++i) {
for (int j = 0; j < cols; ++j) {
  const int index = i * cols + j;
  C[index] = A[index] - B[index];
}
}
return 0;
}

void matrix_copy(int rows,int cols,float *A,float *B)
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
        B[i*cols+j]=A[i*cols+j];
        }
    
    }


}