/* N X N 행렬이여야 함. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start, finish, used_time = 0;    //실행 시간 측정을 위한 변수


void inputValue(int **m, int row, int col);
void outputValue(int **m, int row, int col);
void multiplicaton(int **x, int **y, int **z, int size);
void CalcTime(void);

int main(void)
{
    int row, col, size;
    printf("Input row(=col) in Matrix:  ");
    scanf("%d", &row); // row와 col 입력 받음

    col = row;
    size = row;

    // printf("%d\n", size);

    int **Matrix_X = malloc(sizeof(int *) * row);
    int **Matrix_Y = malloc(sizeof(int *) * row);
    int **Matrix_Z = malloc(sizeof(int *) * row);
    /*
        이중 포인터에 (int 포인터 크기 * row) 만큼 동적 메모리 할당. - 배열의 세로
    */

    for (int i = 0; i < row; i += 1) // 세로 크기만큼 반복
    {
        Matrix_X[i] = malloc(sizeof(int) * col);
        Matrix_Y[i] = malloc(sizeof(int) * col);
        Matrix_Z[i] = malloc(sizeof(int) * col);
        /*
            (int 크기 * row) 만큼 동적 메모리 할당. - 배열의 세로
        */
    }

    inputValue(Matrix_X, row, col);
    inputValue(Matrix_Y, row, col);

    // 시간 계산
    start=clock();
    multiplicaton(Matrix_X, Matrix_Y, Matrix_Z, size);
    finish=clock();
    CalcTime();

    for (int i = 0; i < row; i += 1) // 세로 크기만큼 반복.
    { 
        free(Matrix_X[i]); // 2차원 배열 가로 공간 메모리 해제
        free(Matrix_Y[i]); // 2차원 배열 가로 공간 메모리 해제
        free(Matrix_Z[i]); // 2차원 배열 가로 공간 메모리 해제
    }

    free(Matrix_X); // 2차원 배열의 세로 공간 메모리 해제
    free(Matrix_Y); // 2차원 배열의 세로 공간 메모리 해제
    free(Matrix_Z); // 2차원 배열의 세로 공간 메모리 해제
    
    return 0;
}

void CalcTime(void)
{
    used_time = finish - start;
    printf("ALL DONE!\n Time: %f sec\n\n",(float)used_time/CLOCKS_PER_SEC);
}

void multiplicaton(int **x, int **y, int **z, int size)
{
    int i, j, k;

    for (i = 0; i < size; i += 1)
    {
        for (j = 0; j < size; j += 1)
        {
            for (k = 0; k < size; k += 1)
            {
                z[i][j] = x[i][k] * y[k][j];
            }
        }
    }


    /* Z 잘나오는지 확인 */
    // for (i = 0; i < size; i += 1)
    // {
    //     for (j = 0; j < size; j += 1)
    //     {
    //         printf("z[%d][%d] = %d\t", i, j, z[i][j]);
    //     }
    //     printf("\n");
    // }
}

void inputValue(int **m, int row, int col)
{
    int random;

    for (int i = 0; i < row; i += 1)
    {
        for (int j = 0; j < col; j += 1)
        {
            
            /* 원하면 랜던함수로도 가능 */
            random = (rand() % 9) + 1;
            m[i][j] = random;

            // m[i][j] = i + j;
        
        }
    }
}


void outputValue(int **m, int row, int col)
{
    printf("\n");

    for (int i = 0; i < row; i += 1)
    {
        for (int j = 0; j < col; j += 1)
        {
            printf("%d", m[i][j]);
        }
        printf("\n");
    }
}
