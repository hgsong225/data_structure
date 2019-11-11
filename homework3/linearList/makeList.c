#include "mypoly.h"
struct List * make_Term(int d){    /* d개의 다항식 만들고 그 리스트를 리턴 해주는 함수 */
	//d개의 식,,,,, 어떻게 선형의 관계를 보장해주지?????
	//어떻게 차수를 내림차순으로 설정해줄수 있을까?
	//방법 1. 무작위의 차수를 설정하고 그것을 해당위치에 삽입 (list search -> insert)
	//방법 2. 생성시에 순서관계를 보장하여 생성. 
	//lets 방법 1. we need to search this list.
	struct List * P = malloc(sizeof(struct List));
	int i, cha;
	double gge;
	P->size = 0;
	/*  loop 0 -> d-1
	make node in random order
	addterm in List
	*/
	for (i = 0; i<d; i++){
		gge = (double)(random(5) + 1);
		cha = random(15);
		struct Term * node = make_Node(gge, cha);
		addTerm_in_List(P, node);
	}
	return P;
}
struct Term * make_Node(double co, int ex){
	struct Term * term = malloc(sizeof(struct Term));
	term->coef = co;
	term->expo = ex;
	term->next = NULL;
	return term;
}
void addTerm_in_List(struct List * L, struct Term * meNode){
	/* list 를 search해가면서 자신이 들어갈 위치를 결정, 그 뒤에 insert. */
	/*  case1 : List->size == 0 <list is Empty

	case2 : meNode^c = tnode^c
	case3 : meNode > tnode
	case4 : meNode < tnode  <we have to travel list
	then here is problem
	1. if meNode->tnode then we cant find former tnode.
	-> so we use two Term. +Qnode.
	Pnode = tnode, Qnode is former.
	so in this case, Qnode->meNode->Pnode
	2. if tnode->meNode then just this
	meNode->next = tnode->next;
	tnode->next = meNode;
	*/
	struct Term * tnode = L->head; /*noew tnode is head term of List*/

	if (L->size == 0){       /*case1 : List is empty*/
		//then meNode is head;
		L->head = meNode;
		meNode->next = NULL;
		L->size += 1;
		return;
	}
	else if (meNode->expo < tnode->expo) /*case 2: meNode->expo < tnode->expo*/
	{   /*L->size =1 인 경우도 잡을 수 있다.*/
		// L -> tnode -> .... 
		//                ^ menode have to insert after tnode(head)  
		struct Term * Qnode = tnode;    //Q is head
		struct Term * Pnode = tnode->next;  //if L->size =1 then Pnode =NULL

		while (Pnode != NULL){
			if (Pnode->expo > meNode->expo){ //then iterate more
				Qnode = Qnode->next;
				Pnode = Pnode->next;
			}//if end
			else if (Pnode->expo< meNode->expo){ //then Q->me->P
				break;
			}
			else if (Pnode->expo == meNode->expo){
				Pnode->coef += meNode->coef;
				if (Pnode->coef == (double)0){
					L->size -= 1;
					Qnode->next = Pnode->next;
					free(Pnode);
					return;
				}
				return;
			}
		}//while end
		//after loop, L-> 1. -> .....-> Q -> me -> P 
		meNode->next = Pnode; //Pnode is real or NULL
		Qnode->next = meNode;
		L->size += 1;
		return;
	}
	else if (meNode->expo > tnode->expo){ /*case 3: L-> meNode -> tnode*/
		meNode->next = tnode;
		L->head = meNode;
		L->size += 1;
		return;
	}
	else if (meNode->expo == tnode->expo){/*case 4: coef is same with head*/
		tnode->coef += meNode->coef;
		if (tnode->coef == 0){
			//then size -1
			L->size -= 1;
			L->head = tnode->next; //we know tnode->next is not NULL
			free(tnode);
		}
	}
}
void String_Listize(List *Dlist, char *line)
{   //token = ax^5
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

    struct Term * t = make_Node(coef, expo);
    /*데이터 삽입*/
    addTerm_in_List(Dlist, t);
}