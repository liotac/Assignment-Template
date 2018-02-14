#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "symbol.h"
#include "memory.h"
#include "error.h"
#include "pretty.h"
#include "code.h"
#include "type.h"

extern FILE *yyin;
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
    if (argc == 3)
    {
        enum MODE mode;
        int OK;
        char *input = argv[1];
        char *file = argv[2];

        if (strcmp(input, "scan") == 0) { mode = SCAN; OK = 1; }
        else if (strcmp(input, "tokens") == 0) { mode = TOKENS; OK = 0; }
        else if (strcmp(input, "parse") == 0) { mode = PARSE; OK = 1; }
        else if (strcmp(input, "pretty") == 0) { mode = PRETTY; OK = 0; }
        else if (strcmp(input, "symbol") == 0) { mode = SYMBOL; OK = 0; }
        else if (strcmp(input, "typecheck") == 0) { mode = TYPECHECK; OK = 1; }
        else if (strcmp(input, "codegen") == 0) { mode = CODEGEN; OK = 1; }
        else { fprintf(stderr, "Incorrect arguments\n"); return -1; }

        yyin = fopen(file, "r");

        if (mode <= TOKENS)
        {
            if (mode == TOKENS) { g_tokens = 1; }
            while (yylex()) {} // Scan only
        }
        else
        {
            yyparse(yyin); // Scan and Parse
            if (mode == PRETTY) 
            { 
                prettyPROG(root); 
            }
            else if (mode == SYMBOL) 
            { 
                symPROG(root); 
                Symbol *s;
                printf("Type\tName\n");
                char *typestr;
                for (int i = 0; i < HashSize; i ++)
                {
                    s = symboltable->table[i];
                    while (s) {
                        switch (s->type)
                        {
                            case INT:
                                typestr = "int";
                                break;
                            case FLOAT:
                                typestr = "float";
                                break;
                            case STRING:
                                typestr = "string";
                                break;
                            case BOOLEAN:
                                typestr = "boolean";
                                break;
                            default:
                                break;
                        }
                        printf("%s\t%s\n", typestr, s->name);
                        s = s->next;
                    }
                }
            }
            else if (mode == TYPECHECK)
            {
                symPROG(root); 
                typePROG(symboltable, root);
            }
            else if (mode == CODEGEN)
            {
                symPROG(root); 
                typePROG(symboltable, root);
                codePROG(root, file);
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
