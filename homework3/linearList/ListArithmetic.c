/*
다항식의 덧셈 뺄셈
항의 갯수는 5에서 10
랜덤하게 두 식을 설정하고 계산
함수를 3개의 파일로 나눔
asdfadsf
- 노드 - 리스트 - 순회 함수 - 계산함수 -+
- main -다항식 생성함수 - random 함수

*/
#include "mypoly.h"
/*
다항식의 덧셈 뺄셈
항의 갯수는 5에서 10
랜덤하게 두 식을 설정하고 계산
함수를 3개의 파일로 나눔
asdfadsf
- 노드 - 리스트 - 순회 함수 - 계산함수 -+
- main -다항식 생성함수 - random 함수

*/
#include "mypoly.h"

struct List * Do_subst(struct List * F, struct List * G){ /* 다항식 뺄셈함수 */
	// F(x)-G(x)
	// considr - minus for G(x)
	struct List * resulto = malloc(sizeof(struct List));
	resulto->size = 0;
	resulto->head = NULL;    //LIST initialized.
	struct Term * lnode = malloc(sizeof(struct Term));  //Term for make List
	lnode->next = NULL;
	struct Term * fnode = F->head;
	struct Term * gnode = G->head;
	//loop till F or G is not null
	while (fnode != NULL && gnode != NULL){
		//case 1: F=G , expo is same
		if (fnode->expo == gnode->expo){
			//then Lcoef = coef(f) - coef(g)
			if (fnode->coef != gnode->coef){
				//if  Lcoef != 0 then add to List
				double coco = fnode->coef - gnode->coef;
				int exex = fnode->expo;
				struct Term * t = (struct Term *)make_Node(coco, exex);
				addTerm_in_List(resulto, t);
			}
			else{
				//Lcoef==0 then we dont have to add in List. 
			}
			// F->next G->next term.
			fnode = fnode->next;
			gnode = gnode->next;
		}
		else{
			//case 2: F!=G expo is different.
			// then check expo of F and G
			if (fnode->expo > gnode->expo){
				//if f>g then 3x^8 - 5x^5
				struct Term * t = (struct Term *)make_Node(fnode->coef, fnode->expo);
				addTerm_in_List(resulto, t);
				fnode = fnode->next;
				continue;
				// add f term to List
				// f = f->next and continue
			}
			else {
				//else if f<g then 4x^2 - 5x^5
				double coco = -(gnode->coef);
				// then we have to add term g with minus-
				// g->coef = 0 -g->coef (보수 만들기)
				// add g term to the List 
				int exex = gnode->expo;
				struct Term * t = (struct Term *)make_Node(coco, exex);
				addTerm_in_List(resulto, t);
				gnode = gnode->next;
				// g = g->next and continue
			}
		}
	}// loop end
	lnode = resulto->head;
	while (lnode->next != NULL){
		lnode = lnode->next;
	}
	// then F&G==null , F null, G null three case;
	//case 1 : G is null and F remains
	if (gnode == NULL && fnode != NULL){
		//then lnode ->next = fnode 
		// f ㅁㅁㅁㅁㅁㅁㅁㅁㅁ
		// g x
		// L ㅁㅁㅁ 
		//       ^ lnode         
		lnode->next = fnode;
	}
	else if (fnode == NULL && gnode != NULL){
		//case 2 : F is null and G remains
		// -g so make it all minus
		// loop for gnode is NULL
		while (gnode != NULL){
			struct Term * t = (struct Term *)make_Node(-(gnode->coef), gnode->expo);
			//gnode -> coef = -gnode->coef
			//add gnode to List
			addTerm_in_List(resulto, t);
			gnode = gnode->next;
			//gnode ->next = gnode
		}// end loop
	}
	else if (fnode == NULL && gnode == NULL){
		//case 3 : we did NULL so , lnode ->next = NULL
	}
	return resulto;
}
struct List * Do_add(struct List * F, struct List *G){    /* 다항식 덧셈함수 */
	//F(x)+G(x)
	struct List * resulto = malloc(sizeof(struct List));
	resulto->size = 0;
	resulto->head = NULL;    //LIST initialized.
	struct Term * lnode = malloc(sizeof(struct Term));  //Term for make List
	struct Term * fnode = F->head;
	struct Term * gnode = G->head;
	while (fnode != NULL &&gnode != NULL){
		//loop till F or G is not null
		//case 1: F=G , expo is same
		if (fnode->expo == gnode->expo){
			//then Lcoef = coef(f) + coef(g)
			double coco = fnode->coef + gnode->coef;
			//if  Lcoef ==0 then NO TERM add to List
			if (coco == 0){}
			else {//else add term to List (Lcoef, Lexpo , Lnext NULL)
				struct Term * t = (struct Term *)make_Node(coco, fnode->expo);
				addTerm_in_List(resulto, t);
			}
			fnode = fnode->next;
			gnode = gnode->next;
			// F->next G->next term.
		}
		//case 2: F!=G expo is different.
		else {
			// then check expo of F and G
			if (fnode->expo > gnode->expo){
				//if f>g then 3x^8 + 5x^5
				struct Term * t = (struct Term *)make_Node(fnode->coef, fnode->expo);
				// add f term to List
				addTerm_in_List(resulto, t);
				fnode = fnode->next;
				// f = f->next and continue
			}
			else{
				//else if f<g then 4x^2 + 5x^5
				struct Term * t = (struct Term *)make_Node(gnode->coef, gnode->expo);
				addTerm_in_List(resulto, t);
				gnode = gnode->next;
				// then we have to add term g  
				// add g term to the List 
				// g = g->next and continue
			}
		}
	}// loop end
	lnode = resulto->head;
	if (resulto->size != 0){
		while (lnode->next != NULL){
			lnode = lnode->next;
		}
	}
	// then F&G==null , F null, G null three case;
	//case 1 : G is null and F remains
	if (gnode == NULL && fnode != NULL){
		if (resulto->size != 0){
			lnode->next = fnode;
		}
		else{
			lnode = fnode; 
			addTerm_in_List(resulto, lnode);
		}
		// lnode-> next = fnode
	}
	//case 2 : F is null and G remains
	else if (fnode == NULL && gnode != NULL){
		// lnode->next = gnode
		if (resulto->size != 0){
			lnode->next = fnode;
		}
		else{
			lnode = fnode;
			addTerm_in_List(resulto, lnode);
		}
	}
	//case 3 : we did NULL so , lnode ->next = NULL

	return resulto;
}

struct List * OperatePoly(struct List * F, struct List * G, char * line){
	// if line == - then sbst
	// if line == + then add
	// with F and G
	// F-G G-F
	// F+G G+F
	struct List * resulta = (struct List *)malloc(sizeof(struct List));
	if (strcmp(line, "F-G") == 0){
		// do sbst f-g
		resulta = Do_subst(F, G);
	}
	else if (strcmp(line, "G-F") == 0){
		// do sbst g-f
		resulta = Do_subst(G, F);
	}
	else if ((strcmp(line, "F+G") == 0) || (strcmp(line, "G+F") == 0)){
		// do add f+g
		resulta = Do_add(F, G);
	}
	else{
		resulta = NULL;
	}
	if (resulta == NULL){
		printf("input fault : wrong sentence, \n Usage : F-G or G-F or F+G\n");
		return (struct List *)(-1);
	}
	return resulta;
}
struct List * add_simple(struct List * F, struct List * G){
	//F(x)+G(x)
	struct List * resulto = malloc(sizeof(struct List));
	resulto->size = 0;
	resulto->head = NULL;    //LIST initialized.
	struct Term * lnode = malloc(sizeof(struct Term));  //Term for make List
	resulto->head = lnode; 
	
	struct Term * fnode = F->head;
	struct Term * gnode = G->head;
	while (fnode != NULL && gnode != NULL){
		//loop till F or G is not null
		//case 1: F=G , expo is same
		if (fnode->expo == gnode->expo){
			//then Lcoef = coef(f) + coef(g)
			double coco = fnode->coef + gnode->coef;
			//if  Lcoef ==0 then NO TERM add to List
			if (coco == 0){}
			else {//else add term to List (Lcoef, Lexpo , Lnext NULL)
				struct Term * t = make_Node(coco, fnode->expo);
				if (resulto->size != 0){
					lnode->next = t;
					lnode = lnode->next;
					resulto->size += 1;
				}
				else {
					resulto->head = t;
					resulto->size += 1;
					lnode = resulto->head;
				}
			}
			fnode = fnode->next;
			gnode = gnode->next;
			// F->next G->next term.
		}
		//case 2: F!=G expo is different.
		else {
			// then check expo of F and G
			if (fnode->expo > gnode->expo){
				//if f>g then 3x^8 + 5x^5
				struct Term * t = make_Node(fnode->coef, fnode->expo);
				// add f term to List
				if (resulto->size == 0){
					resulto->head = t;
					resulto->size += 1;
					lnode = resulto->head;
				}
				else{
					lnode->next = t;
					lnode = lnode->next;
					resulto->size += 1;
				}
				fnode = fnode->next;
				// f = f->next and continue
			}
			else{
				//else if f<g then 4x^2 + 5x^5
				struct Term * t = make_Node(gnode->coef, gnode->expo);
				if (resulto->size == 0){
					resulto->head = t;
					resulto->size += 1;
					lnode = resulto->head;
				}
				else{ // resulto->size !=0 , list has more than one node
					lnode->next = t;
					lnode = lnode->next;
					resulto->size += 1;
				}
				gnode = gnode->next;
				// then we have to add term g  
				// add g term to the List 
				// g = g->next and continue
			}
		}
	}// loop end
	// lnode is last node of List resulto
	// then F&G==null , F null, G null three case;
	//case 1 : G is null and F remain
	if (gnode == NULL && fnode != NULL){
		if (resulto->size == 0){
			resulto->head = fnode;
			resulto->size += 1;
		}
		else
			lnode->next = fnode;
		// lnode-> next = fnode
	}
	//case 2 : F is null and G remains
	else if (fnode == NULL && gnode != NULL){
		if (resulto->size ==0){
			//+1만 있으면?
			resulto->head = gnode;
			resulto->size += 1;
		}
		else
			lnode->next = gnode;
		// lnode-> next = fnode
	}
	//case 3 : we did NULL so , lnode ->next = NULL
	return resulto;
}