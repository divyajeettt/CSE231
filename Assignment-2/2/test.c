#include <stdio.h>
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
    float matrix1[3][4] = {
        {1.24, 5.95, 2.41, 7.80},
        {3.14, 6.28, 9.81, 2.72},
        {4.13, 7.00, 8.19, 1.41}
    };

    float matrix2[3][4] = {
        {3.09, 2.71, 6.14, 9.66},
        {6.28, 3.14, 9.72, 1.81},
        {7.01, 5.53, 1.61, 8.19}
    };

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