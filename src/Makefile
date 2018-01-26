CC = gcc
CFLAGS = -Wall
main: lex.yy.o parser.tab.o
	$(CC) lex.yy.o -o minic
lex.yy.c: minic.l
	flex minic.l
clean:
	rm lex.yy.*; rm *.o; rm minic
