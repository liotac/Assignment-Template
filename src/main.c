#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "symbol.h"
#include "memory.h"
#include "error.h"
#include "pretty.h"

int yylex();
void yyparse();

int g_tokens;
PROG *root;
extern SymbolTable *symboltable;

enum MODE {
    SCAN,
    TOKENS,
    PARSE,
    PRETTY,
    SYMBOL,
    TYPECHECK,
    CODEGEN
} MODE;

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        enum MODE mode;
        int OK;
        char *input = argv[1];

        if (strcmp(input, "scan") == 0) { mode = SCAN; OK = 1; }
        else if (strcmp(input, "tokens") == 0) { mode = TOKENS; OK = 0; }
        else if (strcmp(input, "parse") == 0) { mode = PARSE; OK = 1; }
        else if (strcmp(input, "pretty") == 0) { mode = PRETTY; OK = 0; }
        else if (strcmp(input, "symbol") == 0) { mode = SYMBOL; OK = 1; }
        else if (strcmp(input, "typecheck") == 0) { mode = TYPECHECK; OK = 1; }
        else if (strcmp(input, "codegen") == 0) { mode = CODEGEN; OK = 0; }
        else { fprintf(stderr, "Incorrect arguments\n"); return -1; }

        if (mode <= TOKENS)
        {
            if (mode == TOKENS) { g_tokens = 1; }
            while (yylex()) {} // Scan only
        }
        else
        {
            yyparse(); // Scan and Parse
            if (mode == PRETTY) 
            { 
                prettyPROG(root); 
            }
            else if (mode == SYMBOL) 
            { 
                symPROG(root); 
                Symbol *s;
                printf("Type\tName\n");
                for (int i = 0; i < HashSize; i ++)
                {
                    s = symboltable->table[i];
                    while (s) {
                        printf("%d\t%s\n", s->type, s->name);
                        s = s->next;
                    }
                }
            }
        }

        if (OK) { printf("OK\n"); }
        return 0;
    }
    else
    {
        fprintf(stderr, "Incorrect number of arguments\n");
        return -1;
    }
}
