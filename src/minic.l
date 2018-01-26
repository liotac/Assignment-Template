%{
#include <stdio.h>
#include <stdlib.h>
int g_tokens;
%}
CHAR [ a-zA-Z0-9$-/:-?{-~!^_`\[\]]
ESCAPE \\[abfnrtv"\\]
BOOL TRUE|FALSE
INT 0|([1-9][0-9]*)
FLOAT (0|[1-9][0-9])*\.[0-9]+
IDENT [a-zA-Z_][a-zA-Z0-9_]*
COMMENT "//".*
%option yylineno
%%
[ \t\r\n]+
"var"                       if (g_tokens) { printf("tVAR\n"); }
"boolean"                   if (g_tokens) { printf("tBOOLEAN\n"); }
"float"                     if (g_tokens) { printf("tFLOAT\n"); }
"int"                       if (g_tokens) { printf("tINT\n"); }
"string"                    if (g_tokens) { printf("tSTRING\n"); }
"while"                     if (g_tokens) { printf("tWHILE\n"); }
"if"                        if (g_tokens) { printf("tIF\n"); }
"else"                      if (g_tokens) { printf("tELSE\n"); }
"print"                     if (g_tokens) { printf("tPRINT\n"); }
"read"                      if (g_tokens) { printf("tREAD\n"); }
";"                         if (g_tokens) { printf("tSEMICOLON\n"); }
":"                         if (g_tokens) { printf("tCOLON\n"); }
"="                         if (g_tokens) { printf("tASSIGN\n"); }
"+"                         if (g_tokens) { printf("tADD\n"); }
"-"                         if (g_tokens) { printf("tSUB\n"); }
"*"                         if (g_tokens) { printf("tMUL\n"); }
"/"                         if (g_tokens) { printf("tDIV\n"); }
"=="                        if (g_tokens) { printf("tEQL\n"); }
"!="                        if (g_tokens) { printf("tNEQ\n"); }
"&&"                        if (g_tokens) { printf("tAND\n"); }
"||"                        if (g_tokens) { printf("tOR\n"); }
"!"                         if (g_tokens) { printf("tNOT\n"); }
"("                         if (g_tokens) { printf("tLPAREN\n"); }
")"                         if (g_tokens) { printf("tRPAREN\n"); }
"{"                         if (g_tokens) { printf("tLBRACE\n"); }
"}"                         if (g_tokens) { printf("tRBRACE\n"); }
{BOOL}                      if (g_tokens) { printf("tBOOLVAL(%s)\n", yytext); }
{INT}                       if (g_tokens) { printf("tINTVAL(%s)\n", yytext); }
{FLOAT}                     if (g_tokens) { printf("tFLOATVAL(%s)\n", yytext); }
\"({CHAR}|{ESCAPE})*\"      if (g_tokens) { printf("tSTRINGVAL(%s)\n", yytext); }
{IDENT}                     if (g_tokens) { printf("tIDENT(%s)\n", yytext); }
{COMMENT}                   if (g_tokens) { printf("tCOMMENTVAL(%s)\n", yytext); }
.                           printf("Error: token(%s) unrecognized on line %d\n", yytext, yylineno); exit(1);
%%
int yywrap()
{
    return 1;
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        if (strcmp(argv[1], "scan"))
        {
            g_tokens = 1;
        }
        else if (strcmp(argv[1], "tokens"))
        {
            g_tokens = 0;
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
    return 0;
}
