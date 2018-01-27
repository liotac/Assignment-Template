%{
#include <stdio.h>
#include <stdlib.h>

extern int yylineno;
int yylex();
int g_tokens;
void yyerror(const char *s) { fprintf(stderr, "Error: (line %d) %s\n", yylineno, s); exit(1); }
%}

%locations
%error-verbose
%union {
    int intval;
    char *strval;
    double fltval;
    int booval;
}
%token <intval> tINT
%token <fltval> tFLOAT
%token <strval> tSTRING
%token <booval> tBOOLEAN
%token <strval> tIDENTIFIER
%token ADD SUB MUL DIV VAR INT FLOAT BOOLEAN STRING LPAREN RPAREN IF ELSE WHILE
%token LBRACE RBRACE NOT NEQ EQL AND OR ASSIGN COLON SEMICOLON PRINT READ

%left OR
%left AND
%left EQL NEQ
%left ADD SUB
%left MUL DIV
%left UMINUS NOT

%start program
%%
program : declarations statements
        ;
declarations : %empty
             | declaration declarations
             ;
declaration : VAR tIDENTIFIER COLON type ASSIGN expression SEMICOLON
            ;
statements : %empty
           | statement statements
           ;
statement : READ tIDENTIFIER SEMICOLON
          | PRINT expression SEMICOLON
          | tIDENTIFIER ASSIGN expression SEMICOLON
          | IF expression LBRACE statements RBRACE optionalelse
          | WHILE expression LBRACE statements RBRACE
          ;
expression : tIDENTIFIER
           | literal
           | expression OR expression
           | expression AND expression
           | expression EQL expression
           | expression NEQ expression
           | expression ADD expression
           | expression SUB expression
           | expression MUL expression
           | expression DIV expression
           | LPAREN expression RPAREN
           | NOT expression
           | SUB expression %prec UMINUS
           ;
literal : tINT | tFLOAT | tSTRING | tBOOLEAN
        ;
type : INT | FLOAT | STRING | BOOLEAN
     ;
optionalelse : %empty
             | ELSE LBRACE statements RBRACE
             ;
%%
