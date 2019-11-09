//
//
//  Created by Jeong Shin on 2019/11/07.
//  Copyright © 2019 Jeong Shin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1024
typedef struct Node
{
    double coef;
    int expo;
    struct Node *next;
    struct Node *prev;
}Node;
Node *NewNode (double coef, int expo)
{
    Node *newnode =(Node*)malloc(sizeof(Node));
    newnode->coef=coef;
    newnode->expo=expo;
    newnode->prev=newnode->next=NULL;
    return newnode;
}
typedef struct DoublyList
{
    Node *tail;
    Node *head;
    int count;
}DoublyList;
void CreateList(DoublyList *Dlist);
void AddData(DoublyList *Dlist, double coef, int expo);
void AddNode(DoublyList *Dlist, char *line);
void PrintList(DoublyList *Dlist);
void MergeNode(DoublyList *Dlist);
double SumCoef(DoublyList *Dlist, Node *curr);
void Attach(DoublyList *result, Node *new);
void Remove(DoublyList *Dlist, Node *curr);
int Compare(int a, int b);
DoublyList OperatePoly(DoublyList *op1, DoublyList *op2, char operator);

int main(int argc, const char * argv[]) {
    char Aline[MAXLINE]; char Bline[MAXLINE]; char operation[4]; char *ptr;
    DoublyList Alist, Blist, Rlist;
    CreateList(&Alist); CreateList(&Blist);
    /*A poly*/
    printf("Enter A>>");
    fgets(Aline, MAXLINE, stdin);
    ptr=strtok(Aline," \t\n");
    while(ptr!=NULL)
    {
        AddNode(&Alist, ptr);
        ptr=strtok(NULL," \t\n");
    }
    MergeNode(&Alist);
    PrintList(&Alist);
    /*B ploy*/
    printf("\n\nEnter B>>");
    fgets(Bline, MAXLINE, stdin);
    ptr=strtok(Bline," \t\n");
    while(ptr!=NULL)
    {
        AddNode(&Blist, ptr);
        ptr=strtok(NULL," \t\n");
    }
    MergeNode(&Blist);
    PrintList(&Blist);
    /*두 다항식의 합 구하고 출력*/
    printf("\n실행할 연산 입력하세요\t USAGE: A-B, B+A\n>>");
    scanf("\n%s", operation);
    Rlist=OperatePoly(&Alist, &Blist, operation[1]);
    MergeNode(&Rlist);
    PrintList(&Rlist);
}

/*이중 연결리스트 객체 생성 (헤드, 테일)*/
void CreateList(DoublyList *Dlist)
{
    Dlist->head=NewNode(0,0);
    Dlist->tail=NewNode(0,0);
    Dlist->head->next=Dlist->tail;
    Dlist->tail->prev=Dlist->head;
    Dlist->count=0;
}

/*이중 연결리스트에 노드를 추가하는 함수*/
void AddNode(DoublyList *Dlist, char *line)
{
    double coef=0; int expo=0, len, index=0; //index는 x의 위치를 가르킨다.
    len=strlen(line);
    
    /*coef에 대한 처리*/
    char *ptr=line; //문자열의 시작 지점 포인터로 지정하여 atof로 숫자로 바꿔준다.
    if (line[0]=='x') //예외 1) coef없이 x만 오는 경우
        coef=1;
    else if ((line[0]=='+'||line[0]=='-')&&line[1]=='x') //예외 2) +x, -x의 경우: index(x의 위치)는 1 coef는 1
    {
        index=1; coef=1;
    }
    else
    {
        for (int i=0; i<len; i++) // x를 만나면 널 값으로 바꾸어 coef를 구한다.
            if (line[i]=='x')
            {
                line[i]='\0';
                index=i;
            }
        coef=atof(ptr);
    }
    
    /*expo에 대한 처리*/
    ptr=&line[index+1]; //ptr을 x의 다음 지점으로 옮겨준다.
    if(ptr[0]=='^') //^가 있으면 expo를 구한다.
    {
        ptr[0]='0';
        expo=atoi(ptr);
    }
    else if(index==0) //예외2) index가 0이면 x가 없음으로 expo는 0
        expo=0;
    else  //x만 혼자 오는 경우
        expo=1;
    
    /*데이터 삽입*/
    AddData(Dlist, coef, expo);
}

/*이중 연결리스트를 head에서 tail까지 출력하는 함수*/
void PrintList(DoublyList *Dlist)
{
    Node *curr=Dlist->head->next;
    printf("총 노드의 수: %d", Dlist->count);
    printf("\nexpo:");
    while (curr!=Dlist->tail)
    {
        printf("%10d", curr->expo);
        curr=curr->next;
    }
    curr=Dlist->head->next;
    printf("\ncoef:");
    while (curr!=Dlist->tail)
    {
        printf("%10.2f", curr->coef);
        curr=curr->next;
    }
}

/*데이터를 노드에 추가하는 함수*/
void AddData(DoublyList *Dlist, double coef, int expo)
{
    Node *new=NewNode(coef, expo);
    new->prev=Dlist->tail->prev;
    new->next=Dlist->tail;
    Dlist->tail->prev->next=new;
    Dlist->tail->prev=new;
    Dlist->count++;
}

/*지수가 같은 노드는 합체, coef가 0인 노드는 삭제하는 함수*/
void MergeNode(DoublyList *Dlist)
{
    Node *seek=Dlist->head->next;
    while (seek!=Dlist->tail)
    {
        seek->coef=SumCoef(Dlist, seek);
        if (seek->coef==0)
        {
            Node *temp=seek->next;
            Remove(Dlist, seek);
            seek=temp;
        }
        else
            seek=seek->next;
    }
    
}

/*지수가 같은 노드들의 coef를 구하는 함수*/
double SumCoef(DoublyList *Dlist, Node *curr) //현재(curr)노드와 같은 expo를 찾아 coef의 합을 구한다.
{
    double sum=curr->coef;
    Node *seek=Dlist->head->next;
    
    while(seek!=Dlist->tail)
    {
        if ((seek->expo==curr->expo)&&(seek!=curr)) //현재 노드와 찾는 노드(seek)가 다른 주소인데 expo가 같으면
        {
            Node *temp=seek->next;
            sum+=seek->coef; //ceof를 합치고
            Remove(Dlist, seek); //seek는 삭제 반환 값은 seek의 다음노드
            seek=temp;
        }
        else
            seek=seek->next;
    }
    return sum;
}

/*노드를 제거하는 함수*/
void Remove(DoublyList *Dlist, Node *curr)
{
    curr->prev->next=curr->next;
    curr->next->prev=curr->prev;
    free(curr);
    Dlist->count--;
}

/*A와 B의 연산을 하는 함수*/
DoublyList OperatePoly(DoublyList *op1, DoublyList *op2, char operator)
{
    DoublyList result;
    CreateList(&result);
    Node *Seek1=op1->head->next;
    Node *Seek2=op2->head->next;
    
    /*연산자가 -일 경우 피연산자 (op2)의 부호를 전부 바꿔준다.*/
    if (operator=='-')
        while (Seek2!=op2->tail)
        {
            Seek2->coef=-Seek2->coef;
            Seek2=Seek2->next;
        }
    Seek2=op2->head->next;
    
    /*두 다항식중 하나가 끝날때까지 연산한다*/
    while(Seek1!=op1->tail&&Seek2!=op2->tail)
    {
        switch (Compare(Seek1->expo, Seek2->expo))
        {
            case 1: //op1.expo > op2.expo
                Attach(&result, Seek1); //result 리스트에 Seek1노드를 붙여준다.
                Seek1=Seek1->next;
                break;
            case 0:
                AddData(&result, Seek1->coef+Seek2->coef, Seek1->expo);
                Seek1=Seek1->next; Seek2=Seek2->next;
                break;
            case -1:
                Attach(&result, Seek2);
                Seek2=Seek2->next;
                break;
        }
    }
    
    /*아직 남은 항들을 연결해준다.*/
    if (Seek1==op1->tail&&Seek2!=op2->tail)
        Attach(&result, Seek2);
    else if (Seek2==op2->tail&&Seek1!=op1->tail)
        Attach(&result, Seek1);
    
    /*현재 result의 tail이 리스트의 끝에 연결이 안되있기 때문에
     result노드의 끝을 찾아서 tail과 연결해준다*/
    Seek1=result.head->next;
    while (Seek1->next!=NULL)
        Seek1=Seek1->next;
    result.tail->prev=Seek1;
    Seek1->next=result.tail;
    return result;
}
/* 리스트에 노드를 연결해준다 (노드 생성X) */
void Attach(DoublyList *result, Node *new)
{
    new->prev=result->tail->prev;
    result->tail->prev->next=new;
    result->tail->prev=new;
    result->count++;
}
/* 지수 비교하여 1, 0, -1을 반환한다 */
int Compare(int a, int b)
{
    if (a>b)
        return 1;
    else if (a==b)
        return 0;
    else
        return -1;
}
