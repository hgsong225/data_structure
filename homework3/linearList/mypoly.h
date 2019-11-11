#ifndef _MYPOLY
#define _MYPOLY


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#define MAXLINE 512
struct List {
	//length of list 
	//address of term2
	int size;
	struct Term * head;

}List;
struct Term {
	//coef 계수
	double coef;
	//expo 차수
	int expo;
	//address of term
	struct Term * next;
}Term;
//makeList
struct List * make_Term(int d);
void addTerm_in_List(struct List * L, struct Term * meNode);
struct Term * make_Node(double co, int ex);
void String_Listize(List *Dlist, char *line);

//ListArithmetic
struct List * Do_subst(struct List *F, struct List * G);
struct List * Do_add(struct List * F, struct  List * G);
struct List * OperatePoly(List * F,List * G, char * line);
//main
int random(int d);
void showList(struct List * list);



#endif