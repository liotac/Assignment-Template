%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
int g_tokens;
%}
CHAR [ a-zA-Z0-9$-/:-?{-~!^_`\[\]]
ESCAPE \\[abfnrtv"\\]
%option yylineno
%option noinput
%option nounput
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
    if (strcmp(yytext, "TRUE") == 0){ yylval.booval = 1; }
    else { yylval.booval = 0; }
    return tBOOLEAN;
}
(0|([1-9][0-9]*))(\.[0-9]+) {
    if (g_tokens){printf("tFLOAT(%s)\n", yytext); }
    yylval.fltval = atof(yytext);
    return tFLOAT;
}
0|([1-9][0-9]*) {
    if (g_tokens){printf("tINT(%s)\n", yytext); }
    yylval.intval = atoi(yytext);
    return tINT;
}
\"({CHAR}|{ESCAPE})*\" {
    if (g_tokens){printf("tSTRING(%s)\n", yytext); }
    yylval.strval = strdup(yytext);
    return tSTRING;
}
[a-zA-Z_][a-zA-Z0-9_]* {
    if (g_tokens){printf("tIDENTIFIER(%s)\n", yytext); }
    yylval.strval = strdup(yytext);
    return tIDENTIFIER;
}

"//".*      if (g_tokens){printf("tCOMMENTVAL(%s)\n", yytext); }
.           fprintf(stderr, "Error: (line %d) %s\n", yylineno, yytext); exit(1);
%%
