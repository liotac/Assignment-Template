C = gcc

CFLAGS = -Wall

main: parser.tab.o lex.yy.o main.o
	$(CC) lex.yy.o parser.tab.o main.o -o minic -lfl

parser.tab.c parser.tab.h: parser.y
	bison --yacc --defines=parser.tab.c --output=parser.tab.h parser.y

lex.yy.c: scanner.l parser.tab.h
	flex scanner.l
clean:
	rm parser.tab.* lex.yy.*; rm *.o
