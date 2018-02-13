CC = gcc
CFLAGS = -Wall

main: parser.tab.o lex.yy.o main.o tree.h tree.o symbol.h symbol.o memory.h memory.o error.h error.o
	$(CC) *.o -o bin/compiler -lfl

# Parser (bison)
parser.tab.c parser.tab.h: parser.y
	bison --yacc --defines=parser.tab.c --output=parser.tab.h parser.y

# Scanner (flex)
lex.yy.c: scanner.l parser.tab.h
	flex -o lex.yy.c scanner.l

# Cleanup
clean:
	rm -f *.o lex.yy.c parser.tab.h parser.tab.c bin/*
