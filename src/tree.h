#include <stdbool.h>

// ----------------------------------------------------------------------------
// Enum types

// Token types
typedef enum {
    IDENT,
    STRING,
    stringlit,
    INT,
    BOOLEAN,
    intlit,
    FLOAT,
    floatlit,
    binaryop,
    OR,
    AND,
    EQL,
    NEQ,
    ADD,
    SUB,
    MUL,
    DIV,
    unaryop,
    NEG,
    NOT
} ExprToken;


// ----------------------------------------------------------------------------
// Node structures definitions

// Program is the root Node
typedef struct PROG {
    DECL *declarations;
    STMT *statements;
} PROG;

// Declaration Node
typedef struct DECL {
    union { SYMBOL *identifier;
            EXPR *expression;
            struct { DECL *elem; DECL *list; } sequence;
    }
} DECL;

// Statement Node
typedef struct STMT {
    enum { READ, PRINT, ASSIGN, IF, IFELSE, WHILE } token;
    union { struct { STMT *elem, STMT *list; } sequence;
            struct { EXPR *condition; STMT *body; } ifS;
            struct { EXPR *condition; STMT *ifpart, STMT *elsepart; } ifelseS;
            struct { EXPR *condition; STMT *body; } whileS;
            struct { SYMBOL *identifier; EXPR *exp; } assignS;
            EXPR *rwS;
    } val;
} STMT;


// Expression Node
typedef struct EXPR {
    ExpToken token ;
    union { char *strE;
            int intE;
            double floatE;
            bool boolE;
            EXPR *unaryE;
            struct {EXPR *left; EXPR *right;} binaryE;
    } val;
} EXPR;

EXPR *NewExpUnary(TokenType token, void *value);
EXPR *NewExpBinary(TokenType token, EXPR *lhs, EXPR *rhs);
