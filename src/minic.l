%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"
typedef enum { false, true } bool;
int g_tokens;
%}
CHAR [ a-zA-Z0-9$-/:-?{-~!^_`\[\]]
ESCAPE \\[abfnrtv"\\]
%option yylineno
%%
[ \t\r\n]+
"var"                       if (g_tokens){printf("VAR\n"); } return VAR;
"boolean"                   if (g_tokens){printf("BOOLEAN\n"); } return BOOLEAN;
"float"                     if (g_tokens){printf("FLOAT\n"); } return FLOAT;
"int"                       if (g_tokens){printf("INT\n"); } return INT;
"string"                    if (g_tokens){printf("STRING\n"); } return STRING;
"while"                     if (g_tokens){printf("WHILE\n"); } return WHILE;
"if"                        if (g_tokens){printf("IF\n"); } return IF;
"else"                      if (g_tokens){printf("ELSE\n"); } return ELSE;
"print"                     if (g_tokens){printf("PRINT\n"); } return PRINT;
"read"                      if (g_tokens){printf("READ\n"); } return READ;
";"                         if (g_tokens){printf("SEMICOLON\n"); } return SEMICOLON;
":"                         if (g_tokens){printf("COLON\n"); } return COLON;
"="                         if (g_tokens){printf("ASSIGN\n"); } return ASSIGN;
"+"                         if (g_tokens){printf("ADD\n"); } return ADD;
"-"                         if (g_tokens){printf("SUB\n"); } return SUB;
"*"                         if (g_tokens){printf("MUL\n"); } return MUL;
"/"                         if (g_tokens){printf("DIV\n"); } return DIV;
"=="                        if (g_tokens){printf("EQL\n"); } return EQL;
"!="                        if (g_tokens){printf("NEQ\n"); } return NEQ;
"&&"                        if (g_tokens){printf("AND\n"); } return AND;
"||"                        if (g_tokens){printf("OR\n"); } return OR;
"!"                         if (g_tokens){printf("NOT\n"); } return NOT;
"("                         if (g_tokens){printf("LPAREN\n"); } return LPAREN;
")"                         if (g_tokens){printf("RPAREN\n"); } return RPAREN;
"{"                         if (g_tokens){printf("LBRACE\n"); } return LBRACE;
"}"                         if (g_tokens){printf("RBRACE\n"); } return RBRACE;

TRUE|FALSE {
    if (g_tokens){printf("tBOOLEAN(%s)\n", yytext); }
    if (strcmp(yytext, "TRUE") == 0){ yyval.boolval = true; }
    else { yyval.boolval = false; }
    return tBOOLEAN;
}
0|([1-9][0-9]*) {
    if (g_tokens){printf("tINT(%s)\n", yytext); }
    yyval.intval = atoi(yytext);
    return tINT;
}
(0|[1-9][0-9])*\.[0-9]+ {
    if (g_tokens){printf("tFLOAT(%s)\n", yytext); }
    yyval.fltval = atofy(yytext);
    return tFLOAT;
}
\"({CHAR}|{ESCAPE})*\" {
    if (g_tokens){printf("tSTRING(%s)\n", yytext); }
    yyval.strval = strdup(yytext);
    return tSTRING;
}
[a-zA-Z_][a-zA-Z0-9_]* {
    if (g_tokens){printf("tIDENTIFIER(%s)\n", yytext); }
    yyval.strval = strdup(yytext);
    return tIDENTIFIER;
}

"//".*      if (g_tokens){printf("tCOMMENTVAL(%s)\n", yytext); }
.           fprintf(stderr, "Error: (line %d) %s\n", yylineno, yytext); exit(1);
%%
int yywrap()
{
    return 1;
}

int main(int argc, char **argv)
{
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
    return 0;
}
