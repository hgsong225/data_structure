CC = gcc -o
Obj1 = add.o
Obj2 = deduct.o
Obj3 = main.o

poly_array : $(Obj1) $(Obj2) $(Obj3)
	$(CC) poly_array $(Obj1) $(Obj2) $(Obj3)
$(Obj1) : mypoly.h add.c
	gcc -c -o $(Obj1) add.c
$(Obj2) : mypoly.h deduct.c
	gcc -c -o $(Obj2) deduct.c
$(Obj3) : mypoly.h main.c
	gcc -c -o $(Obj3) main.c

clean : 
	rm -f *.o
	rm poly_array