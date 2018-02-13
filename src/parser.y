%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"
#include "error.h"

extern PROG *root; // Root of our AST
extern int g_tokens; // Global compiler mode token: prints all tokens, one per line

extern int yylineno;
int yylex();
void yyerror(const char *error)
{
    fprintf(stderr, "Error: (line %d) %s during PARSE\n", yylineno, error);
    exit(1);
}
%}
%locations
%error-verbose
%code requires
{
    #include "tree.h"
    #include <stdbool.h>
}

%union {
    int ival;
    float fval;
    bool bval;
    char *sval;
    char *identifier;
    PROG *prog;
    DECL *decl;
    STMT *stmt;
    EXPR *expr;
}

%type <prog> program
%type <decl> declarations declaration
%type <stmt> statements statement
%type <expr> expression

%token <ival> btINT
%token <fval> btFLOAT
%token <sval> btSTRING
%token <bval> btBOOLEAN
%token <identifier> btIDENT
%token bADD bSUB bMUL bDIV bNOT bNEQ bEQL bAND bOR bASSIGN bVAR bCOLON bSEMICOLON
%token bLBRACE bRBRACE bPRINT bREAD bLPAREN bRPAREN bIF bELSE bWHILE
%token bINT bFLOAT bBOOLEAN bSTRING 

%left bOR
%left bAND
%left bEQL bNEQ
%left bADD bSUB
%left bMUL bDIV
%left bUMINUS bNOT

%start program
%%
program : declarations statements { root = newPROG(yylineno, $1, $2); }
        ;
declarations : %empty { $$ = NULL; }
             | declaration declarations { $$ = newDECLseq(yylineno, $1, $2); }
             ;
declaration : bVAR btIDENT bCOLON bINT bASSIGN expression bSEMICOLON { $$ = newDECLdeclaration(yylineno, $2, $6, INT); }
            | bVAR btIDENT bCOLON bFLOAT bASSIGN expression bSEMICOLON { $$ = newDECLdeclaration(yylineno, $2, $6, FLOAT); }
            | bVAR btIDENT bCOLON bBOOLEAN bASSIGN expression bSEMICOLON { $$ = newDECLdeclaration(yylineno, $2, $6, BOOLEAN); }
            | bVAR btIDENT bCOLON bSTRING bASSIGN expression bSEMICOLON { $$ = newDECLdeclaration(yylineno, $2, $6, STRING); }
            ;
statements : %empty { $$ = NULL; }
           | statement statements { $$ = newSTMTseq(yylineno, $1, $2); }
           ;
statement : bREAD btIDENT bSEMICOLON { $$ = newSTMTread(yylineno, $2); }
          | bPRINT expression bSEMICOLON {$$ = newSTMTprint(yylineno, $2); }
          | btIDENT bASSIGN expression bSEMICOLON { $$ = newSTMTassignment(yylineno, $1, $3); }
          | bIF expression bLBRACE statements bRBRACE { $$ = newSTMTif(yylineno, $2, $4); }
          | bIF expression bLBRACE statements bRBRACE bELSE bLBRACE statements bRBRACE { $$ = newSTMTifel(yylineno, $2, $4, $8); }
          | bWHILE expression bLBRACE statements bRBRACE { $$ = newSTMTwhile(yylineno, $2, $4); }
          ;
expression : btIDENT { $$ = newEXPRidentifier(yylineno, $1); }
           | btINT { $$ = newEXPRint(yylineno, $1); }
           | btFLOAT { $$ = newEXPRfloat(yylineno, $1); }
           | btSTRING  { $$ = newEXPRstring(yylineno, $1); }
           | btBOOLEAN { $$ = newEXPRbool(yylineno, $1); }
           | expression bOR expression { $$ = newEXPRbinary(yylineno, OR, $1, $3); }
           | expression bAND expression { $$ = newEXPRbinary(yylineno, AND, $1, $3); }
           | expression bEQL expression { $$ = newEXPRbinary(yylineno, EQL, $1, $3); }
           | expression bNEQ expression { $$ = newEXPRbinary(yylineno, NEQ, $1, $3); }
           | expression bADD expression { $$ = newEXPRbinary(yylineno, ADD, $1, $3); }
           | expression bSUB expression { $$ = newEXPRbinary(yylineno, SUB, $1, $3); }
           | expression bMUL expression { $$ = newEXPRbinary(yylineno, MUL, $1, $3); }
           | expression bDIV expression { $$ = newEXPRbinary(yylineno, DIV, $1, $3); }
           | bLPAREN expression bRPAREN { $$ = $2; }
           | bNOT expression { $$ = newEXPRunary(yylineno, NOT, $2); }
           | bSUB expression %prec bUMINUS { $$ = newEXPRunary(yylineno, NEG, $2); }
           ;
%%
