#include <stdio.h>

#define MAX 20
int front = -1;
int rear = -1;
int queue[MAX];

int IsEmpty(void);
int isFull(void);
void enqueue(int value);
int dequeue();

int main(){
    int i = 0;

    for (i = 0; i < MAX; i += 1)
    {
        enqueue(i + 1);
    }

    for (i = 0; i < MAX; i += 1)
    {
        printf("Dequeued Data: %d\n", dequeue());
    }
    dequeue();
    
    return 0;
}


 /* 비었는지 확인 */
int IsEmpty(void)
{
    if (front == rear) //front와 rear가 같으면 큐는 비어있는 상태 
        return 1;
    else return 0;
}


 /* 큐가 꽉 찼는지 확인 */
int IsFull(void)
{
    int tmp = (rear + 1) % MAX; //원형 큐에서 rear + 1을 MAX로 나눈 나머지값이
    if (tmp == front) //front와 같으면 큐는 가득차 있는 상태 
        return 1;
    else
        return 0;
}

/* 큐 넣기 */
void enqueue(int value)
{
    if (IsFull())
        printf("Queue is Full.\n");
    else
        queue[++rear] = value;
}

/* 큐 빼기 */
int dequeue()
{
    if(IsEmpty())
        printf("Queue is Empty.\n");
    else {
        front = (front + 1) % MAX;
        return queue[front];
    }
}