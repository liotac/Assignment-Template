// Node definitions of the Abstract Syntax Tree for the MiniLang Compiler
#include <stdbool.h>

// ----------------------------------------------------------------------------
// Node identification type

typedef enum {
    ERR,
    SEQ,
    DECLARE // declaration are always assignments in MiniLang
} DeclType;

typedef enum {
    ERR,
    SEQ,
    WHILE, IF, IFELSE,  // conditionals
    READ, PRINT,        // CLI expressions
    ASSIGN              // assignment
} StmtType;

typedef enum {
    ERR,
    IDENT,                                  // variables
    STRING, INT, BOOLEAN, FLOAT,            // literals
    OR, AND, EQL, NEQ, ADD, SUB, MUL, DIV,  // binary operators
    NEG, NOT                                // unary operators
} ExprType;

// ----------------------------------------------------------------------------
// Node structure definition

typedef struct PROG {
    int lineno;
    DECL *declarations;
    STMT *statements;
} PROG;

typedef struct DECL {
    int lineno;
    DeclType type;
    union { struct { char *identifier; ExprType type, EXPR *expression; } declaration;
            struct { DECL *element; DECL *list; } seq;
    } val;
} DECL;

typedef struct STMT {
    int lineno;
    StmtType type;
    union { struct { char *identifier; EXPR *expression; } assignment;
            struct { STMT *element, STMT *list; } seq;
            struct { EXPR *condition; STMT *body; } cond; //if/while
            struct { EXPR *condition; STMT *ifpart, STMT *elsepart; } ifel;
            EXPR *rdpr; // read/print
    } val;
} STMT;

typedef struct EXPR {
    int lineno;
    ExpType type ;
    union { char *identifier;
            char *sLit;
            int iLit;
            float fLit;
            bool bLit;
            EXPR   *unary;
            struct {EXPR *left; EXPR *right;} binary;
    } val;
} EXPR;

// ----------------------------------------------------------------------------
// Node constructors signature

PROG *newPROG(int lineno, DECL *declarations, STMT *statements);

DECL *newDECLdeclaration(int lineno, char *identifier, ExprType type, EXPR *expression);
DECL *newDECLseq(int lineno, DECL *element, DECL *list);

STMT *newSTMTassignment(int lineno, char *identifier, EXPR *expression);
STMT *newSTMTseq(int lineno, STMT *element, STMT *list);
STMT *newSTMTif(int lineno, EXPR *condition, STMT *body);
STMT *newSTMTwhile(int lineno, EXPR *condition, STMT *body);
STMT *newSTMTifel(int lineno, EXPR *condition, STMT *ifpart, STMT *elsepart);
STMT *newSTMTread(int lineno, EXPR *rdpr);
STMT *newSTMTprint(int lineno, EXPR *rdpr);

EXPR *newEXPRidentifier(int lineno, char *identifier);
EXPR *newEXPRstring(int lineno, char *stringLiteral);
EXPR *newEXPRint(int lineno, int *intLiteral);
EXPR *newEXPRfloat(int lineno, float *floatLiteral);
EXPR *newEXPRbool(int lineno, bool *boolLiteral);
EXPR *newEXPRunary(int lineno, ExprType type, EXPR *unaryExpression);
EXPR *newEXPRbinary(int lineno, ExprType type, EXPR *leftExpression, EXPR *rightExpression);
