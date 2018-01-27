#include <stdio.h>

void yyparse();
int main(int argc, char **argv)
{
    /*
    if (argc == 2)
    {
        if (strcmp(argv[1], "scan") == 0)
        {
            g_tokens = 0;
        }
        else if (strcmp(argv[1], "tokens") == 0)
        {
            g_tokens = 1;
        }
    }
    else
    {
        printf("Incorrent argument\n");
        return -1;
    }
    while (yylex()) {}
    if (!g_tokens)
    {
        printf("OK\n");
    }
    */
    yyparse();
    printf("OK\n");
    return 0;
}
