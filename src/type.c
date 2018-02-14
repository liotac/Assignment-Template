#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "error.h"
#include "type.h"

void typePROG(SymbolTable *t, PROG *p)
{
    typeDECL(t, p->declarations);
    typeSTMT(t, p->statements);
}

void typeDECL(SymbolTable *t, DECL *d)
{ 
    int lhs, rhs;
    if (d) {
        switch (d->type)
        {
            case SEQ:
                 typeDECL(t, d->val.seq.element);
                 typeDECL(t, d->val.seq.list);
                 break;
            case DECLARATION:
                 lhs = d->val.declaration.type;
                 rhs = typeEXPR(t, d->val.declaration.expression);
                 if (lhs != rhs)
                 {
                     panic(d->lineno, d->val.declaration.identifier, "type doesnt match rhs");
                 }
                 break;
            default:
                panic(d->lineno, "TYPECHECK", "DECL");
        }
    }
}

void typeSTMT(SymbolTable *t, STMT *s)
{
    int lhs, rhs, cnd;
    Symbol *sym;
    if (s) {
        switch (s->type)
        {
            case SEQ:
                typeSTMT(t, s->val.seq.element);
                typeSTMT(t, s->val.seq.list);
                break;
            case WHILE:
            case IF:
                cnd = typeEXPR(t, s->val.cond.condition);
                if (!(cnd == INT || cnd == BOOLEAN))
                {
                    panic(s->lineno, "TYPECHECK", "STMT WHILE");
                }
                typeSTMT(t, s->val.cond.body);
                break;
            case IFELSE:
                cnd = typeEXPR(t, s->val.ifel.condition);
                if (!(cnd == INT || cnd == BOOLEAN))
                {
                    panic(s->lineno, "TYPECHECK", "STMT IFELSE");
                }
                typeSTMT(t, s->val.ifel.ifpart);
                typeSTMT(t, s->val.ifel.elsepart);
                break;
            case READ:
                break;
            case PRINT:
                cnd = typeEXPR(t, s->val.printexpr);
                if (!(cnd == INT || cnd == FLOAT || cnd == BOOLEAN || cnd == STRING))
                {
                    panic(s->lineno, "TYPECHECK", "STMT PRINT");
                }
                break;
            case ASSIGNMENT:
                sym = getSymbol(t, s->val.assignment.identifier);
                lhs = sym->type;
                rhs = typeEXPR(t, s->val.assignment.expression);
                if (lhs != rhs)
                {
                    if (!(lhs == FLOAT && rhs == INT))
                    {
                        panic(s->lineno, s->val.assignment.identifier, "type doesn't match rhs");
                    }
                }
                break;
            default:
                panic(s->lineno, "TYPECHECK", "STMT");
        }
    }
}

int typeEXPR(SymbolTable *t, EXPR *e)
{
    int lhs, rhs;
    Symbol *sym;
    if (e) {
        switch (e->type)
        {
            case IDENT:
                sym = getSymbol(t, e->val.identifier);
                return sym->type;
            case STRING:
            case INT:
            case BOOLEAN:
            case FLOAT:
                return e->type;
            case OR:
            case AND:
            case EQL:
            case NEQ:
            case ADD:
            case SUB:
            case MUL:
            case DIV:
                lhs = typeEXPR(t, e->val.binary.left);
                rhs = typeEXPR(t, e->val.binary.right);
                switch (e->type)
                {
                    case OR:
                    case AND:
                        if ((lhs == INT || lhs == BOOLEAN) && (rhs == INT || rhs == BOOLEAN))
                        {
                            return BOOLEAN;
                        }
                        else
                        {
                            panic(e->lineno, "TYPECHECK", "EXPR AND/OR");
                        }
                    case EQL:
                    case NEQ:
                        if (lhs == rhs)
                        {
                            return BOOLEAN;
                        }
                        else
                        {
                            panic(e->lineno, "TYPECHECK", "EXPR EQL/NEQ");
                        }
                    case ADD:
                        if (lhs == STRING && rhs == STRING)
                        {
                            return STRING;
                        }
                    case MUL:
                        if ((lhs == STRING && rhs == INT) || (lhs == INT && rhs == STRING))
                        {
                            return STRING;
                        }
                    case SUB:
                    case DIV:
                        if (lhs == BOOLEAN || rhs == BOOLEAN)
                        {
                            panic(e->lineno, "TYPECHECK", "EXPR OPERATION");
                        }
                        else if (lhs == STRING || rhs == STRING)
                        {
                            panic(e->lineno, "TYPECHECK", "EXPR OPERATION");
                        }
                        else if (lhs == rhs)
                        {
                            return lhs;
                        }
                        else if ((lhs == FLOAT && rhs == INT) || (lhs == INT || rhs == FLOAT))
                        {
                            return FLOAT;
                        }
                        else
                        {
                            panic(e->lineno, "TYPECHECK", "EXPR OPERATION");
                        }
                    default:
                        break;
                        panic(e->lineno, "TYPECHECK", "EXPR OPERATION");
                }
            case NEG:
                lhs = typeEXPR(t, e->val.unary);
                if (lhs == INT || lhs == FLOAT)
                {
                    return lhs;
                }
                else
                {
                    panic(e->lineno, "TYPECHECK", "EXPR NEG");
                }
            case NOT:
                lhs = typeEXPR(t, e->val.unary);
                if (lhs == BOOLEAN)
                {
                    return lhs;
                }
                else
                {
                    panic(e->lineno, "TYPECHECK", "EXPR BOOLEAN");
                }
            default:
                panic(e->lineno, "TYPECHECK", "STMT");
        }
    }
    panic(e->lineno, "TYPECHECK", "EXPR");
    return -1;
}
