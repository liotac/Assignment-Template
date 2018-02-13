#include <stdio.h>
#include <string.h>

int yylex();
void yyparse();

int g_tokens;
extern PROG *root;

enum {
    SCAN,
    TOKENS,
    PARSE,
    PRETTY,
    SYMBOL,
    TYPECHECK,
    CODEGEN
} Compiler;

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        Compiler mode;
        int OK = 0;
        char *input = argv[1];

        if (strcmp(input, "scan") == 0) mode = SCAN; OK = 1;
        else if (strcmp(input, "tokens") == 0) mode = TOKENS;
        else if (strcmp(input, "parse") == 0) mode = PARSE; OK = 1;
        else if (strcmp(input, "pretty") == 0) mode = PRETTY;
        else if (strcmp(input, "symbol") == 0) mode = SYMBOL;
        else if (strcmp(input, "typecheck") == 0) mode = TYPECHECK; OK = 1;
        else if (strcmp(input, "codegen") == 0) mode = CODEGEN;
        else fprintf(stderr, "Incorrect arguments\n"); return -1;

        switch(mode)
        {
            case TOKENS :
                g_tokens = 1;
            case SCAN :
                while (yylex()) {}
                break;
            case CODEGEN:
            case TYPECHECK:
            case SYMBOL:
            case PRETTY:
            case PARSE :
                yyparse();
                break;
        }
        if (OK) { printf("OK\n"); }
        return 0;
    }
    else fprintf(stderr, "Incorrect number of arguments\n"); return -1;
}
