CC = gcc
CFLAGS = -Wall

main: fb.scanner.o fb.parser.o tree.h tree.o symbol.h symbol.o error.h error.o memory.h memory.o pretty.h pretty.o type.h type.o main.o
	$(CC) fb.scanner.o fb.parser.o tree.o symbol.o error.o memory.o pretty.o type.o main.o -o bin/compiler -lfl

# Parser (bison)
fb.parser.c fb.parser.h: parser.y
	bison --yacc --defines=fb.parser.c --output=fb.parser.h parser.y

# Scanner (flex)
fb.scanner.c: scanner.l fb.parser.h
	flex -o fb.scanner.c scanner.l

# Cleanup
clean:
	rm -f bin/* out/* fb.*
