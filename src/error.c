#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void panic(char *error, int lineno)
{
    fprintf(stderr, "ERROR: (line %d) %s\n", lineno, error);
    exit(1);
}

void panicMsg(char *error, int lineno, char *msg)
{
    fprintf(stderr, "ERROR: (line %d) %s, %s\n", lineno, error, msg);
    exit(1);
}

void yyerror(const char *error)
{
    fprintf(stderr, "Error: (line %d) %s\n", yylineno, error);
    exit(1);
}
