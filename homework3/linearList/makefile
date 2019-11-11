#32152332 ����ȣ makefile
#��������Ʈ�� ����� ���׽� ���� �E��
CC = gcc -o
Obj1 = List_Arithmetic.o
Obj2 = makeList.o
Obj3 = main.o

linear_Arithmetic : $(Obj1) $(Obj2) $(Obj3)
	$(CC) linear_Arithmetic $(Obj1) $(Obj2) $(Obj3)
$(Obj1) : mypoly.h ListArithmetic.c
	gcc -c -o $(Obj1) ListArithmetic.c
$(Obj2) : mypoly.h makeList.c
	gcc -c -o $(Obj2) makeList.c
$(Obj3) : mypoly.h main.c
	gcc -c -o $(Obj3) main.c

clean : 
	rm -f *.o
	rm linear_Arithmetic
