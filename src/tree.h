#ifndef TREE_H
#define TREE_H
// Node definitions of the Abstract Syntax Tree for the MiniLang Compiler
#include <stdbool.h>

// ----------------------------------------------------------------------------
// Node identification type

typedef enum {
    SEQ,
    DECLARATION,
    WHILE, IF, IFELSE,  // conditionals
    READ, PRINT,        // CLI expressions
    ASSIGNMENT,             // assignment
    IDENT,                                  // variables
    STRING, INT, BOOLEAN, FLOAT,            // literals
    OR, AND, EQL, NEQ, ADD, SUB, MUL, DIV,  // binary operators
    NEG, NOT                                // unary operators
} Type;

// ----------------------------------------------------------------------------
// Node structure definition

typedef struct EXPR {
    int lineno;
    Tyoe type ;
    union { char *identifier;
            char *sval;
            int ival;
            float fval;
            bool bval;
            struct EXPR *unary;
            struct {EXPR *left; EXPR *right;} binary;
    } val;
} EXPR;

typedef struct DECL {
    int lineno;
    Type type;
    union { struct { char *identifier; EXPR *expression; Type type } declaration;
            struct { struct DECL *element; struct DECL *list; } seq;
    } val;
} DECL;

typedef struct STMT {
    int lineno;
    Type type;
    union { struct { char *identifier; EXPR *expression; } assignment;
            struct { struct STMT *element; struct STMT *list; } seq;
            struct { EXPR *condition; struct STMT *body; } cond; //if/while
            struct { EXPR *condition; struct STMT *ifpart; STMT *elsepart; } ifel;
            EXPR *printexpr;
            char *identifier;
    } val;
} STMT;

typedef struct PROG {
    int lineno;
    DECL *declarations;
    STMT *statements;
} PROG;

// ----------------------------------------------------------------------------
// Node constructors signature

PROG *newPROG(int lineno, DECL *declarations, STMT *statements);

DECL *newDECLdeclaration(int lineno, char *identifier, EXPR *expression, Type type);
DECL *newDECLseq(int lineno, DECL *element, DECL *list);

STMT *newSTMTassignment(int lineno, char *identifier, EXPR *expression);
STMT *newSTMTseq(int lineno, STMT *element, STMT *list);
STMT *newSTMTif(int lineno, EXPR *condition, STMT *body);
STMT *newSTMTwhile(int lineno, EXPR *condition, STMT *body);
STMT *newSTMTifel(int lineno, EXPR *condition, STMT *ifpart, STMT *elsepart);
STMT *newSTMTread(int lineno, char *identifier);
STMT *newSTMTprint(int lineno, EXPR *printexpr);

EXPR *newEXPRidentifier(int lineno, char *identifier);
EXPR *newEXPRstring(int lineno, char *stringLiteral);
EXPR *newEXPRint(int lineno, int *intLiteral);
EXPR *newEXPRfloat(int lineno, float *floatLiteral);
EXPR *newEXPRbool(int lineno, bool *boolLiteral);
EXPR *newEXPRunary(int lineno, Type type, EXPR *unaryExpression);
EXPR *newEXPRbinary(int lineno, Type type, EXPR *leftExpression, EXPR *rightExpression);
#endif
