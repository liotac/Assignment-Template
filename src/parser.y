%{
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

// Root of our AST
extern Exp *root;

// Global compiler mode token: prints all tokens, one per line
int g_tokens;

// Flex stuff
extern int yylineno;
int yylex();
void yyerror(const char *s) { fprintf(stderr, "Error: (line %d) %s\n", yylineno, s); exit(1); }
%}

%locations
%error-verbose
%code requires
{
    #include "tree.h"
}

%union {
    void *value;
    Exp *exp;
}

%type <exp> program exp

%token <intval> btINT
%token <fltval> btFLOAT
%token <strval> btSTRING
%token <booval> btBOOLEAN
%token <strval> btIDENT
%token bADD bSUB bMUL bDIV bVAR bINT bFLOAT bBOOLEAN bSTRING bLPAREN bRPAREN bIF bELSE bWHILE
%token bLBRACE bRBRACE bNOT bNEQ bEQL bAND bOR bASSIGN bCOLON bSEMICOLON bPRINT bREAD

%left bOR
%left bAND
%left bEQL bNEQ
%left bADD bSUB
%left bMUL bDIV
%left bUMINUS bNOT

%start program
%%
program : declarations statements { root =$1; }
        ;
declarations : %empty
             | declaration declarations
             ;
declaration : bVAR btIDENT bCOLON type bASSIGN expression bSEMICOLON
            ;
statements : %empty
           | statement statements
           ;
statement : bREAD btIDENT bSEMICOLON
          | bPRINT expression bSEMICOLON
          | btIDENT bASSIGN expression bSEMICOLON
          | bIF expression bLBRACE statements bRBRACE optionalelse
          | bWHILE expression bLBRACE statements bRBRACE
          ;
expression : btIDENT
           | literal
           | expression bOR expression
           | expression bAND expression
           | expression bEQL expression
           | expression bNEQ expression
           | expression bADD expression
           | expression bSUB expression
           | expression bMUL expression
           | expression bDIV expression
           | bLPAREN expression bRPAREN
           | bNOT expression
           | bSUB expression %prec bUMINUS
           ;
literal : btINT | btFLOAT | btSTRING | btBOOLEAN
        ;
type : bINT | bFLOAT | bSTRING | bBOOLEAN
     ;
optionalelse : %empty
             | bELSE bLBRACE statements bRBRACE
             ;
%%
