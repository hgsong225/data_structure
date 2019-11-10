#include "mypoly.h"
int random(int d){     /*0 ~ d-1 범위의 random num return*/
	int r = rand() % d;
	return r;
}

void showList(struct List * list){
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
	int r;
	int i = 0;
	struct List * Fx = malloc(sizeof(struct List));
	struct List * Gx = malloc(sizeof(struct List));
	struct List * Qx = malloc(sizeof(struct List));

	srand(time(NULL));
	while (i < 6){
		r = random(15) + 5; Fx = make_Term(r); /*항의 개수는 5부터 19사이 랜덤 한 값*/
		r = random(15) + 5; Gx = make_Term(r); /*항의 개수는 5부터 19사이 랜덤 한 값*/
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
	}
    system("PAUSE");
	return 0;
}
