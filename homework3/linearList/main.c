#include "mypoly.h"
int random(int d){     /*0 ~ d-1 범위의 random num return*/
	int r = rand() % d;
	return r;
}

void showList(struct List * list){
	if (list == NULL){
		printf("0\n"); return;
	}
	struct Term * tnode = list->head;
	printf("%d, ", list->size);
	while (tnode != NULL){
		printf("%.2fx", tnode->coef);
		printf("^%d  ", tnode->expo);
		tnode = tnode->next;
	}
	puts("");
	return;
}
int main(){
	int i = 0;
	/*srand(time(NULL));
	while (i < 6){
	r = random(15) + 5; Fx = make_Term(r);
	r = random(15) + 5; Gx = make_Term(r);
	printf("\n\n%d번째 ", i + 1);
	puts("---------------------------------------------------");
	printf("F(x) :"); showList(Fx);
	printf("G(x) :"); showList(Gx);

	Qx = Do_subst(Fx, Gx);
	printf("\n F-G : "); showList(Qx);

	//	showList_inArray(Qx, Fx, Gx);

	//printf("\nF(x) :"); showList(Fx);
	//printf("G(x) :"); showList(Gx);

	Qx = Do_add(Fx, Gx);
	printf("\n F+G : "); showList(Qx);

	//printf("\nF(x) :"); showList(Fx);
	//printf("G(x) :"); showList(Gx);
	i++;
	}*/
	 char operation[4]; char *ptr;
	/*A poly*/
	while (i<6){
		char * Aline = (char *)malloc(sizeof(char)*MAXLINE);
		struct List * Fx = malloc(sizeof(struct List));
		struct List * Gx = malloc(sizeof(struct List));
		struct List * Qx = malloc(sizeof(struct List));
		Fx = make_Term(0); Gx = make_Term(0);

		printf("%d번째 +--------------------------+\n", i + 1);
		printf("Enter F>>");
		fgets(Aline, MAXLINE, stdin);
		ptr = strtok(Aline, " \t\n");
		while (ptr != NULL)
		{
			String_Listize(Fx, ptr);
			ptr = strtok(NULL, " \t\n");
		}
		/*B ploy*/
		printf("\n\nEnter G>>");
		fgets(Aline, MAXLINE, stdin);
		ptr = strtok(Aline, " \t\n");
		while (ptr != NULL)
		{
			String_Listize(Gx, ptr);
			ptr = strtok(NULL, " \t\n");
		}
		//free(Aline);
		/*두 다항식의 합 구하고 출력*/
		printf("simple addition : ");
		Qx = add_simple(Fx, Gx);
		showList(Qx);
		printf("\n실행할 연산 입력하세요\t USAGE: F-B, F+G\n>>");
		fgets(operation, 4, stdin);
		Qx = OperatePoly(Fx, Gx, operation);
		if (Qx == NULL){ continue; }
		showList(Qx); i++; free(Fx); free(Gx); free(Qx);
		fflush(stdin);
	}
	system("PAUSE");
	return 0;
}
