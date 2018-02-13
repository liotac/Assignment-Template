%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fb.parser.h"
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
extern int g_tokens;
int yylex();
%}
symbol [-~@#$%^&*+/`<>=_|'.,;:!?{}\[\]() ]
character [a-zA-Z0-9]
escape \\[abfnrtv"\\]
%option yylineno
%option noinput
%option nounput
%%
[ \t\r\n]+
"var"                       if (g_tokens){printf("VAR\n"); } return bVAR;
"boolean"                   if (g_tokens){printf("BOOLEAN\n"); } return bBOOLEAN;
"float"                     if (g_tokens){printf("FLOAT\n"); } return bFLOAT;
"int"                       if (g_tokens){printf("INT\n"); } return bINT;
"string"                    if (g_tokens){printf("STRING\n"); } return bSTRING;
"while"                     if (g_tokens){printf("WHILE\n"); } return bWHILE;
"if"                        if (g_tokens){printf("IF\n"); } return bIF;
"else"                      if (g_tokens){printf("ELSE\n"); } return bELSE;
"print"                     if (g_tokens){printf("PRINT\n"); } return bPRINT;
"read"                      if (g_tokens){printf("READ\n"); } return bREAD;
";"                         if (g_tokens){printf("SEMICOLON\n"); } return bSEMICOLON;
":"                         if (g_tokens){printf("COLON\n"); } return bCOLON;
"="                         if (g_tokens){printf("ASSIGN\n"); } return bASSIGN;
"+"                         if (g_tokens){printf("ADD\n"); } return bADD;
"-"                         if (g_tokens){printf("SUB\n"); } return bSUB;
"*"                         if (g_tokens){printf("MUL\n"); } return bMUL;
"/"                         if (g_tokens){printf("DIV\n"); } return bDIV;
"=="                        if (g_tokens){printf("EQL\n"); } return bEQL;
"!="                        if (g_tokens){printf("NEQ\n"); } return bNEQ;
"&&"                        if (g_tokens){printf("AND\n"); } return bAND;
"||"                        if (g_tokens){printf("OR\n"); } return bOR;
"!"                         if (g_tokens){printf("NOT\n"); } return bNOT;
"("                         if (g_tokens){printf("LPAREN\n"); } return bLPAREN;
")"                         if (g_tokens){printf("RPAREN\n"); } return bRPAREN;
"{"                         if (g_tokens){printf("LBRACE\n"); } return bLBRACE;
"}"                         if (g_tokens){printf("RBRACE\n"); } return bRBRACE;

TRUE|FALSE {
    if (g_tokens){printf("tBOOLEAN(%s)\n", yytext); }
    if (strcmp(yytext, "TRUE") == 0){ yylval.bval = 1; }
    else { yylval.bval = 0; }
    return btBOOLEAN;
}
(0|([1-9][0-9]*))(\.[0-9]+) {
    if (g_tokens){printf("tFLOAT(%s)\n", yytext); }
    yylval.fval = atof(yytext);
    return btFLOAT;
}
0|([1-9][0-9]*) {
    if (g_tokens){printf("tINT(%s)\n", yytext); }
    yylval.ival = atoi(yytext);
    return btINT;
}
\"({character}|{symbol}|{escape})*\" {
    if (g_tokens){printf("tSTRING(%s)\n", yytext); }
    yylval.sval = strdup(yytext);
    return btSTRING;
}
[a-zA-Z_][a-zA-Z0-9_]* {
    if (g_tokens){printf("tIDENT(%s)\n", yytext); }
    yylval.identifier = strdup(yytext);
    return btIDENT;
}

"//".*      if (g_tokens){printf("tCOMMENT(%s)\n", yytext); }
.           fprintf(stderr, "Error: (line %d) %s\n", yylineno, yytext); exit(1);
%%
