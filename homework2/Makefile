CircularQ : sort.o
    gcc -o sort sort.o

CircularQ.o : sort.c
    gcc -c -o sort.o sort.c

InfixToPostfix : InfixToPostfix.o
    gcc -o InfixToPostfix InfixToPostfix.o

InfixToPostfix.o : InfixToPostfix.c
    gcc -c -o InfixToPostfix.o InfixToPostfix.c

clean :
    rm *.0 sort matrix