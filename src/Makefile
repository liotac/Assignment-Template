C = gcc

CFLAGS = -Wall

main: parser-mini.tab.o lex-mini.yy.o main-mini.o
	$(CC) lex-mini.yy.o parser-mini.tab.o main-mini.o -o compiler-mini -lfl

parser-mini.tab.c parser-mini.tab.h: parser-mini.y
	bison --yacc --defines=parser-mini.tab.c --output=parser-mini.tab.h parser-mini.y

lex-mini.yy.c: scanner-mini.l parser-mini.tab.h
	flex -o lex-mini.yy.c scanner-mini.l
clean:
	rm parser-mini.tab.* lex-mini.yy.*; rm *.o; rm compiler-mini
