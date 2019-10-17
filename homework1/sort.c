#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
 
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))    //SWAP함수 설정

clock_t start, finish, used_time = 0;    //실행 시간 측정을 위한 변수
int n; //데이터의 개수를 받는 전역변수 설정

//버블 정렬
void bubble_sort(int list[], int n)
{
    int i, j, tmp;
    printf("Bubble Sorting... ");
    for (i = n - 1; i > 0; i -= 1)
    {
        for (j = 0; j < i; j += 1)
            if (list[j] > list[j + 1])
                SWAP(list[j], list[j + 1], tmp);
    }
}
 
//선택 정렬
void selection_sort(int list[], int n)
{
    int i, j, least, tmp;
    
    printf("Selection Sorting... ");
    for(i = 0; i < n - 1; i += 1)
    {
        least = i;
        for (j = i + 1; j < n; j += 1)
            if (list[j] < list[least]) least = j;
        SWAP(list[i], list[least], tmp);
    }
}
 
//삽입 정렬
void insertion_sort(int list[], int n)
{
    int i, j, key;
    printf("Insertion Sorting... ");
    for(i = 1; i < n; i += 1)
    {
        key = list[i];
        for(j = i - 1; j >= 0 && list[j] > key; j -= 1)
            list[j + 1] = list[j];
        list[j + 1] = key;
    }
}
 
//원본 배열을 복사하는 함수
void CopyArr(int list[], int original[])
{
    int i;
    for(i = 0; i < n; i += 1)
        list[i] = original[i];
}
 
//실행 시간을 측정 및 출력하는 함수
void CalcTime(void)
{
    used_time = finish - start;
    printf("ALL DONE!\n Time: %f sec\n\n",(float)used_time/CLOCKS_PER_SEC);
}


void main ()
{
    int *arr;
    const int size;
    int i;

    printf("Input data size: ");
    scanf("%d", &size);

    arr = (int *)malloc(sizeof(int) * size);

    int original[size];    //랜덤함수로 만든 데이터를 저장할 원본 배열
    int list[size];    //각 정렬 알고리즘에서 사용할 데이터 배열
    
    n = size;
    for(i = 0; i < n; i += 1)
        original[i]=rand();
    
    printf("number of data : %d\n\n", n);
 
    CopyArr(list, original);
    start = clock();
    selection_sort(list, n);
    finish = clock();
    CalcTime();

    CopyArr(list, original);
    start=clock();
    insertion_sort(list, n);
    finish=clock();
    CalcTime();
 
    CopyArr(list, original);
    start = clock();
    bubble_sort(list, n);
    finish = clock();
    CalcTime();
}