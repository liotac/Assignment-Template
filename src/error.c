#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void panic(int lineno, char *error, char *msg)
{
    fprintf(stderr, "ERROR: (line %d) %s %s\n", lineno, error, msg);
    exit(1);
}
