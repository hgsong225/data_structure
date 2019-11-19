#include<stdio.h>
#include<stdlib.h>
#define MAX 20
struct node { // 트리를 구성하는 노드의 구조체 선언
    char value;
    struct node* alink; // left
    struct node* blink; // right
};

struct node* tree = NULL; //트리를 가리키는 해더
char poly[MAX]; // 산술식을 입력받을 배열
char ope1[MAX]; // 연산자 스택 배열
struct node* ope2[MAX]; // 피연산자 스택 배열(노드의 주소값을 가짐)

/* 스택에 필요한 함수들 */
void pushOpe1(char a);
void popOpe1();
int full1();
int empty1();
int top1 = 0;
void pushOpe2(struct node* a);
struct node* popOpe2();
int full2();
int empty2();
int top2 = 0;

void changeTree(); // 산술식을 트리로 만들어 주는 함수
struct node* makeNode(char); // 하나의 노드를 만들어 주소값을 반환
void makeOneTree(char); // 한개의 루트 아래 두개의 subtree를 가지는 트리 생성
void inOrder(struct node*); // infix 출력
void preOrder(struct node*); // prefix 출력
void postOrder(struct node*); // postfix 출력
int isp(char a); // 연산자에 대한 level값 반환

int main() {
    printf("Please enter an infix math expression = ");
    gets(poly);
    changeTree();
    printf("changeTree is OK\n");
    printf("inOrder = ");
    inOrder(tree);
    printf("\npreOrder = ");
    preOrder(tree);
    printf("\npostOrder = ");
    postOrder(tree);
    printf("\n");
    return 0;
}

void changeTree() {
    int i;
    char data;
    for(i = 0; i < MAX; i += 1) {
        data = poly[i];

        if (data == 0) break;
        else if (data == '(') {
            pushOpe1(data);
        }
        else if (data == ')') {
            while(ope1[top1 - 1] != '(') {
                makeOneTree(ope1[top1 - 1]);
                popOpe1();
            }
            popOpe1();
        }
        else if (data == '+' || data == '-' || data == '*' || data == '/') {
            if (top1 == 0) pushOpe1(data);
            else if (isp(ope1[top1 - 1]) >= isp(data)) {
                makeOneTree(ope1[top1 - 1]);
                popOpe1();
                pushOpe1(data);
            }
            else pushOpe1(data);
        }
        else{
            pushOpe2(makeNode(data));
        }
    }
    while(!empty1()) {
        makeOneTree(ope1[top1 - 1]);
        popOpe1();
    }
}

struct node* makeNode(char a) { // char a에 대한 노드 생성
    struct node* newnode;
    newnode = (struct node*)malloc(sizeof(struct node)); // 추가할 노드 생성
    newnode -> value = a;
    newnode -> alink = NULL;
    newnode -> blink = NULL;
    return newnode; // 생성된 노드의 주소값 반환
}

void makeOneTree(char a) {
    struct node* onenode;
    onenode = makeNode(a);
    tree = onenode;

    onenode -> blink = popOpe2();
    onenode -> alink = popOpe2();
    pushOpe2(onenode);
}

void inOrder(struct node* T) {
    if (T != NULL) {
        inOrder(T -> alink);
        printf("%c", T -> value);
        inOrder(T -> blink);
    }
}

void preOrder(struct node* T) {
    if (T != NULL) {
        printf("%c", T -> value);
        preOrder(T -> alink);
        preOrder(T -> blink);
    }
}
void postOrder(struct node* T) {
    if (T != NULL) {
        postOrder(T -> alink);
        postOrder(T -> blink);
        printf("%c", T -> value);
    }
}

int isp(char a) {
    if (a == '(') return 0;
    else if (a == '+' || a == '-') return 1;
    else if (a == '*' || a == '/') return 2;
    else return 3;
}


/* 배열을 이용한 스택 1 */
void pushOpe1(char a) {
    if (!full1()) {
        ope1[top1] = a;
        top1 += 1;
    }
    else printf("Ope1 is FULL\n");
}

void popOpe1() {
    if (!empty1()) {
    top1 -= 1;

    }
    else printf("Ope1 is EMPTY\n");
}

int full1() {
    if (top1 == MAX) return 1;
    else return 0;
}

int empty1() {
    if (top1 == 0) return 1;
    else return 0;
}

/* 배열을 이용한 스택 2 */
void pushOpe2(struct node* a) {
    if (!full2()) {
        ope2[top2] = a;
        top2 += 1;
    }
    else printf("Ope2 is FULL\n");
}

struct node* popOpe2() {
    struct node* tmp;
    if (!empty2()) {
        top2 -= 1;
        tmp = ope2[top2];
    }
    else printf("Ope2 is EMPTY\n");
    return tmp;
}
int full2() {
    if (top2 == MAX) return 1;
    else return 0;
}

int empty2() {
    if (top2 == 0) return 1;
    else return 0;
}