CC = gcc
CFLAGS = -Wall
minic: lex.yy.o
	$(CC) lex.yy.o -o minic
lex.yy.c: minic.l
	flex minic.l
clean:
	rm lex.yy.*; rm *.o; rm minic
