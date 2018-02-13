#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "tree.h"
#include "symbol.h"
#include "memory.h"
#include "error.h"

// ----------------------------------------------------------------------------
// Constructors for SYMBOL and SymbolTable

int Hash(char *str)
{ int hash = 0;
    while (*str) hash = (hash << 1) + *str++;
    return hash % HashSize;
}

SymbolTable *newSymbolTable()
{ SymbolTable *t;
    t = NEW(SymbolTable);
    for (int i = 0; i < HashSize; i++) t->table = NULL;
    return t;
}

SYMBOL *putSYMBOL(SymbolTable *t, char *name, ExprType type, int lineno)
{ SYMBOL *s
    int i = Hash(name);
    for (s = t->table[i]; s; s= s->next)
    {
        if (strcmp(s->name, name) == 0) {
            panicMsg(name, lineno, "identifier was already declared");
        }
    }
    s = NEW(SYMBOL);
    s->name = name;
    s->type = type;
    s->next = t->table[i];
    t->table[i] = s;
    return s;
}

SYMBOL *getSYMBOL(SymbolTable *t, char *name)
{ SYMBOL *s;
    int i = Hash(name);
    for (s = t->table[i]; s; s = s->next)
    {
        if (strcmp(s->name, name) == 0) return s;
    }
    return NULL;
}

// ----------------------------------------------------------------------------
// Symbol traversing


void symPROG(SymbolTable *t, PROG *p)
{
    symboltable = newSymbolTable();
    symDECL(t, program->val.declarations);
    symSTMT(t, program->val.statements);
}

void symDECL(SymbolTable *t, DECL *d)
{
    switch (d->type)
    {
        case SEQ:
             symDECL(t, d->val.element);
             symDECL(t, d->val.list);
             break;
        case DECLARE:
             SYMBOL *s = putSYMBOL(t, d->val.identifier, d->type);
             symEXPR(t, d->val.expression);
             break;
    }
}

void symSTMT(SymbolTable *t, STMT *s)
{
    switch (e->type)
    {
        case SEQ:
            symSTMT(t, s->val.element);
            symSTMT(t, s->val.list);
            break;
        case WHILE:
            symEXPR(t, s->val.condition);
            symSTMT(t, s->val.body);
            break;
        case IF:
            symEXPR(t, s->val.condition);
            symSTMT(t, s->val.body);
            break;
        case IFELSE:
            symEXPR(t, s->val.condition);
            symSTMT(t, s->val.ifpart);
            symSTMT(t, s->val.elsepart);
            break;
        case READ:
            symEXPR(t, s->val.rdpr);
            break;
        case PRINT:
            symEXPR(t, s->val.rdpr);
            break;
        case ASSIGN:
            SYMBOL *i = getSYMBOL(t, s->val.identifier);
            symEXPR(t, s->val.expression);
            break;
    }
}

void symEXPR(SymbolTable *t, EXPR *e)
{
    switch (e->type)
    {
        case IDENT:
            Symbol *id = getSymbol(t, e->val.identifier);
            if (i == NULL)
            {
                panicMsg(e->val.identifier, e->lineno, "identifier not declared yet");
            }
    }
}
