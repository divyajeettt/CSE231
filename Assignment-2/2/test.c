#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

#define sys_kernel_2d_memcpy 469

///////////////////////////////////////////////////////////////////////////////////////////////////

void printMatrix(float **matrix, int m, int n)
{
    for (int i=0; i < m; i++)
    {
        for (int j=0; j < n; j++)
        {
            printf("%f\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


int main()
{
    int n = 5;
    int m = 5;

    float **matrix1 = (float **)malloc(n * sizeof(float *));
    float **matrix2 = (float **)malloc(n * sizeof(float *));

    for (int i=0; i < n; i++)
    {
        matrix1[i] = (float *)malloc(m * sizeof(float));
        matrix2[i] = (float *)malloc(m * sizeof(float));
    }

    float counter = 1.0;
    for (int i=0; i < n; i++)
    {
        for (int j=0; j < m; j++)
        {
            matrix1[i][j] = counter++;
            matrix2[i][j] = 0.0;
        }
    }

    printf("Matrix 2 before copying: \n");
    printMatrix(matrix2, 3, 4);

    if (syscall(sys_kernel_2d_memcpy, matrix1, matrix2, 3, 4) < 0)
    {
        perror("syscall not functioning");
        return 1;
    }

    printf("Matrix 2 after copying: \n");
    printMatrix(matrix2, 3, 4);

    return 0;
}