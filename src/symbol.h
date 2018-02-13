#include <stdbool.h>
#include "tree.h"

#define HashSize 317

typedef struct SYMBOL {
    char *name;
    ExprType type;
    struct SYMBOL *next;
    union {
        char *sLit;
        int iLit;
        float fLit;
        bool bLit;
    } val;
}

typedef struct SymbolTable { Symbol *table[HashSize]; } SymbolTable;

SymbolTable *newSymbolTable();

SYMBOL *putSymbol(SymbolTable *t, char *name, ExprType type, int lineno);
SYMBOL *getSymbol(SymbolTable *t, char *name);

int symPROG(SymbolTable *t, PROG *program);
int symDECL(SymbolTable *t, DECL *declarations);
int symSTMT(SymbolTable *t, STMT *statements);
int symEXPR(SymbolTable *t, EXPR *expressions);

// ----------------------------------------------------------------------------
// Global SymbolTable
//
SymbolTable *symboltable;
