#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "tree.h"
#include "symbol.h"
#include "memory.h"
#include "error.h"

// ----------------------------------------------------------------------------
// Constructors for Symbol and SymbolTable

int Hash(char *str)
{ int hash = 0;
    while (*str) hash = (hash << 1) + *str++;
    return hash % HashSize;
}

SymbolTable *newSymbolTable()
{ SymbolTable *t;
    t = NEW(SymbolTable);
    for (int i = 0; i < HashSize; i++) t->table[i] = NULL;
    return t;
}

Symbol *putSymbol(SymbolTable *t, char *name, Type type)
{ Symbol *s;
    int i = Hash(name);
    for (s = t->table[i]; s; s= s->next)
    {
        if (strcmp(s->name, name) == 0) {
            return NULL;
        }
    }
    s = NEW(Symbol);
    s->name = name;
    s->type = type;
    s->next = t->table[i];
    t->table[i] = s;
    return s;
}

Symbol *getSymbol(SymbolTable *t, char *name)
{ Symbol *s;
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
    symDECL(t, p->declarations);
    symSTMT(t, p->statements);
}

void symDECL(SymbolTable *t, DECL *d)
{
    Symbol *sym;
    switch (d->type)
    {
        case SEQ:
             symDECL(t, d->val.seq.element);
             symDECL(t, d->val.seq.list);
             break;
        case DECLARATION:
             if ((sym = putSymbol(t, d->val.declaration.identifier, d->type)) == NULL)
             {
                 panic(d->lineno, d->val.declaration.identifier, "already declared");
             }
             symEXPR(t, d->val.declaration.expression);
             break;
        default:
            panic(d->lineno, "SYMBOL", "DECL");
    }
}

void symSTMT(SymbolTable *t, STMT *s)
{
    Symbol *sym;
    switch (s->type)
    {
        case SEQ:
            symSTMT(t, s->val.seq.element);
            symSTMT(t, s->val.seq.list);
            break;
        case WHILE:
            symEXPR(t, s->val.cond.condition);
            symSTMT(t, s->val.cond.body);
            break;
        case IF:
            symEXPR(t, s->val.cond.condition);
            symSTMT(t, s->val.cond.body);
            break;
        case IFELSE:
            symEXPR(t, s->val.ifel.condition);
            symSTMT(t, s->val.ifel.ifpart);
            symSTMT(t, s->val.ifel.elsepart);
            break;
        case READ:
            if ((sym = getSymbol(t, s->val.identifier)) == NULL)
            {
                panic(s->lineno, s->val.identifier, "undeclared");
            }
            break;
        case PRINT:
            symEXPR(t, s->val.printexpr);
            break;
        case ASSIGNMENT:
            if ((sym = getSymbol(t, s->val.assignment.identifier)) == NULL)
            {
                panic(s->lineno, s->val.assignment.identifier, "undeclared");
            }
            symEXPR(t, s->val.assignment.expression);
            break;
        default:
            panic(s->lineno, "SYMBOL", "STMT");
    }
}

void symEXPR(SymbolTable *t, EXPR *e)
{
    Symbol *sym;
    switch (e->type)
    {
        case IDENT:
            if ((sym = getSymbol(t, e->val.identifier)) == NULL)
            {
                panic(e->lineno, e->val.identifier, "undeclared");
            }
        case STRING:
        case INT:
        case BOOLEAN:
        case FLOAT:
        case OR:
        case AND:
        case EQL:
        case NEQ:
        case ADD:
        case SUB:
        case MUL:
        case DIV:
        case NEG:
        case NOT:
            break;
        default:
            panic(e->lineno, "SYMBOL", "STMT");
    }
}
