#include <stdio.h>
#include <string.h>

int yylex();
int g_tokens;
void yyparse();
int main(int argc, char **argv)
{
    if (argc == 2)
    {
        int mode;
        int ok = 1;
        if (strcmp(argv[1], "scan") == 0) { mode = 1; }
        if (strcmp(argv[1], "tokens") == 0) { mode = 2; ok = 0; }
        if (strcmp(argv[1], "parse") == 0) { mode = 3; }
        switch(mode)
        {
            case 2 :
                g_tokens = 1;
            case 1 :
                while (yylex()) {}
                break;
            case 3 :
                yyparse();
        }
        if (ok) { printf("OK\n"); }
        return 0;
    }
    else
    {
        fprintf(stderr, "Incorrect arguments\n");
        return -1;
    }
        /*
        if (strcmp(argv[1], "scan") == 0)
        {
            g_tokens = 0;
            ok_mode = 1;
            scan_mode = 1;
        }
        else if (strcmp(argv[1], "tokens") == 0)
        {
            g_tokens = 1;
            ok_mode = 0;
            scan_mode = 1;
        }
        else if (strcmp(argv[1], "parse") == 0)
        {
            ok_mode = 1;
            scan_mode = 0;
        }
        else
        {
            fprintf(stderr, "Incorrect arguments\n");
            return -1;
        }
    }
    else
    {
        fprintf(stderr, "Incorrect arguments\n");
        return -1;
    }
    while (yylex()) {}
    if (!g_tokens)
    {
        printf("OK\n");
    }
    yyparse();
    printf("OK\n");
    return 0;
    */
}
