#ifndef SYMBOL_H
#define SYMBOL_H
#include <stdbool.h>
#include "tree.h"

#define HashSize 317

typedef struct Symbol {
    char *name;
    Type type;
    struct Symbol *next;
    union {
        char *sval;
        int ival;
        float fval;
        bool bval;
    } eval;
} Symbol;

typedef struct SymbolTable { Symbol *table[HashSize]; } SymbolTable;

SymbolTable *newSymbolTable();

Symbol *putSymbol(SymbolTable *t, char *name, Type type);
Symbol *getSymbol(SymbolTable *t, char *name);

void symPROG(PROG *program);
void symDECL(SymbolTable *t, DECL *declarations);
void symSTMT(SymbolTable *t, STMT *statements);
void symEXPR(SymbolTable *t, EXPR *expressions);

// ----------------------------------------------------------------------------
// Global SymbolTable

SymbolTable *symboltable;
#endif
