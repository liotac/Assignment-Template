%{
#include <stdio.h>
#include <stdlib.h>

extern int yylineno;
int yylex();
void yyerror(const char *s){ fprintf(stderr, "Error: (line %d) %s\n", yylineno, s); exit(1;) }
typedef enum { false, true } bool;
%}

%locations
%error-verbose
%union {
    int intval;
    char *strval;
    double fltval;
    bool booval;
}
%token <intval> tINT
%token <fltval> tFLOAT
%token <strval> tSTRING
%token <booval> tBOOLEAN
%token <strval> tIDENTIFIER
%token ADD SUB MUL DIV VAR INT FLOAT BOOLEAN STRING LPAREN RPAREN IF ELSE WHILE
%token LBRACE RBRACE NOT NEQ EQL AND OR

%left ADD SUB
%left MUL DIV
%left UMINUS

%start program
%%
program : declarations statements
        ;
declarations : %empty
             | declaration declarations
             ;
declaration : VAR tIDENTIFIER COLON INT ASSIGN tINT SEMICOLON
            | VAR tIDENTIFIER COLON FLOAT ASSIGN tFLOAT SEMICOLON
            | VAR tIDENTIFIER COLON BOOLEAN ASSIGN tBOOLEAN SEMICOLON
            | VAR tIDENTIFIER COLON STRING ASSIGN tSTRING SEMICOLON
            ;
statements : %empty
           | statement statements
           ;
statement : READ tIDENTIFIER
          | PRINT expression
          | tIDENTIFIER ASSIGN expression
          | IF expression LBRACE statements RBRACE optionalelse
          | WHILE expression LBRACE statements RBRACE
          ;
expression : tIDENTIFIER
           | literal
           | expression ADD expression
           | expression SUB expression
           | expression MUL expression
           | expression DIV expression
           | LPAREN expression RPAREN
           | SUB expression %prec UMINUS
           ;
literal : tINT | tFLOAT | tSTRING | tBOOLEAN
        ;
optionalelse : %empty
             | ELSE LBRACE statements RBRACE
             ;
