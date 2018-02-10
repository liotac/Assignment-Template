CC = gcc
CFLAGS = -Wall

main: bin/parser.tab.o bin/lex.yy.o bin/main.o
	$(CC) bin/lex.yy.o bin/parser.tab.o bin/main.o -o bin/compiler -lfl

bin/main.o: main.c
	$(CC) -c main.c -o bin/main.o

# Parser (bison)
bin/parser.tab.c bin/parser.tab.h: parser.y
	bison --yacc --defines=bin/parser.tab.c --output=bin/parser.tab.h parser.y

# Scanner (flex)
bin/lex.yy.c: scanner.l bin/parser.tab.h
	flex -o bin/lex.yy.c scanner.l

# Cleanup
clean:
	rm -f bin/*
