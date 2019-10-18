// C program for Sparse Matrix Representation 
// using Linked Lists 
#include<stdio.h> 
#include<stdlib.h> 

// 희소 행렬을 표현하기 위한 구조체
struct Node 
{ 
	int value;
	int row_index;
	int col_index;
	struct Node *next;
};

int probabilityOfZero(int prob, int digits);
void inputValue(int **m, int row, int col);
void outputValue(int **m, int row, int col);
void createNewNodes(struct Node** start, int non_zero_element, int row_index, int column_index);
void printList(struct Node* start);
int allAddValues(struct Node* start);

void main()
{
    int row, col;

    printf("Input row in Matrix:  ");
    scanf("%d", &row);
    printf("Input col in Matrix:  ");
    scanf("%d", &col);

    int **Matrix = malloc(sizeof(int *) * row);
    
    for (int i = 0; i < row; i += 1)
    {
        Matrix[i] = malloc(sizeof(int) * col);
    }

    inputValue(Matrix, row, col);
    outputValue(Matrix, row, col);

	// 빈 리스트로 시작
	struct Node* start = NULL;

	for (int i = 0; i < row; i += 1)
    {
		for (int j = 0; j < col;j += 1) 
        {
            // 0이 아닌 값만 넘김
			if (Matrix[i][j] != 0) 
				createNewNodes(&start, Matrix[i][j], i, j);
        }
    }

	printList(start);
    allAddValues(start);

    for (int i = 0; i < row; i += 1) // 세로 크기만큼 반복.
    { 
        free(Matrix[i]); // 2차원 배열 가로 공간 메모리 해제
    }

    free(Matrix); // 2차원 배열의 세로 공간 메모리 해제
}

/* prob = 0이 나올 확률, digits = 자릿수 */ 
int probabilityOfZero(int prob, int digits)
{
    return ((rand() % 100) < prob) ? 0 : (rand() % digits);
}

/* 각 행렬에 값 삽입 */
void inputValue(int **m, int row, int col)
{
    int rand;
    for (int i = 0; i < row; i += 1)
    {
        for (int j = 0; j < col;j += 1)
        {
            rand = probabilityOfZero(90, 10); // 90% 확률로 0 생성, 열자리 수
            m[i][j] = rand;
        }
    }
}

/* 생성한 행렬 보여주기 */
void outputValue(int **m, int row, int col)
{
    printf("%d x %d Sparse Matrix with a 90 percent probabilty of zero. \n", row, col);

    for (int i = 0; i < row; i += 1)
    {
        for (int j = 0; j < col;j += 1)
        {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

/* 새 노드 생성 */
void createNewNodes(struct Node** start, int non_zero_element, int row_index, int column_index) 
{ 
    struct Node *temp, *r;
    temp = *start;
    if (temp == NULL) 
    {
    // 동적 노드 생성
    temp = (struct Node *) malloc (sizeof(struct Node));
    temp -> value = non_zero_element;
    temp -> row_index = row_index;
    temp -> col_index = column_index;
    temp -> next = NULL;
    *start = temp;
    } 
    else
    { 
        while (temp -> next != NULL)
        {
            temp = temp -> next;

            // 동적 노드 생성
            r = (struct Node *) malloc (sizeof(struct Node));
            r -> value = non_zero_element;
            r -> row_index = row_index;
            r -> col_index = column_index;
            r -> next = NULL;
            temp -> next = r;
        }
    }
} 

/* Linked List의 내용을 처음부터 출력 */
void printList(struct Node* start) 
{
    struct Node *temp, *r, *s;
    temp = r = s = start;

    printf("row_index: ");
    while(temp != NULL) 
    { 
        printf("%d ", temp -> row_index);
        temp = temp -> next;
    } 
    printf("\n");

    printf("col_index: ");
    while(r != NULL) 
    { 
        printf("%d ", r -> col_index);
        r = r -> next;
    } 
    printf("\n");

    printf("value: ");
    while(s != NULL) 
    { 
        printf("%d ", s -> value);
        s = s -> next;
    } 
    printf("\n");
}

/* Linked List 모든 value 값 총합 (희소 행렬내 0이 아닌 수 들의 총합) */
int allAddValues(struct Node* start)
{
    int total = 0; 

    struct Node *s;
    s = start;

    while (s != NULL)
    {
        total += s -> value;
        s = s -> next;
    }
    printf("TOTAL: %d", total);
}