%{
#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
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
"var"                       printf("tVAR\n");
"boolean"                   printf("tBOOLEAN\n");
"float"                     printf("tFLOAT\n");
"int"                       printf("tINT\n");
"string"                    printf("tSTRING\n");
"while"                     printf("tWHILE\n");
"if"                        printf("tIF\n");
"else"                      printf("tELSE\n");
"print"                     printf("tPRINT\n");
"read"                      printf("tREAD\n");
";"                         printf("tSEMICOLON\n");
":"                         printf("tCOLON\n");
"="                         printf("tASSIGN\n");
"+"                         printf("tADD\n");
"-"                         printf("tSUB\n");
"*"                         printf("tMUL\n");
"/"                         printf("tDIV\n");
"=="                        printf("tEQL\n");
"!="                        printf("tNEQ\n");
"&&"                        printf("tAND\n");
"||"                        printf("tOR\n");
"!"                         printf("tNOT\n");
"("                         printf("tLPAREN\n");
")"                         printf("tRPAREN\n");
"{"                         printf("tLBRACE\n");
"}"                         printf("tRBRACE\n");
{BOOL}                      printf("tBOOLVAL(%s)\n", yytext);
{INT}                       printf("tINTVAL(%s)\n", yytext);
{FLOAT}                     printf("tFLOATVAL(%s)\n", yytext);
\"({CHAR}|{ESCAPE})*\"      printf("tSTRINGVAL(%s)\n", yytext);
{IDENT}                     printf("tIDENT(%s)\n", yytext);
{COMMENT}                   printf("tCOMMENTVAL(%s)\n", yytext);
.                           printf("Error: token(%s) unrecognized on line %d\n", yytext, yylineno); exit(1);
%%
int yywrap()
{
    return 1;
}

int main()
{
    yylex();
    printf("\n");
    return 0;
}
