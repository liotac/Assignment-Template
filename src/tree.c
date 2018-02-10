#include <stdlib.h>
#include "tree.h"


// ----------------------------------------------------------------------------
// Exp (node) constructors

Exp *NewExpUnary(TokenType token, void *value)
{
    Exp *e = malloc(sizeof(Exp));
    e->Line = yylineno;
    e->Token = token;
    if (token > unaryop)
    {
        e->Val.Unary = (Exp*) value;
    }
    else
    {
        if (token < stringlit)
        {
            e->Val.String = (char*) value;
        }
        else if (token < intlit)
        {
            e->Val.Int = (int*) value;
        else if (token < floatlit)
        {
            e->Val.Float = (double*) value;
        }
        else
            printf("NewExpUnary could not resolve (void*) value type\n");
            exit(EXIT_FAILURE);
        }
    }
    return e;
}

Exp *NewExpBinary(TokenType token, Exp *lhs, Exp *rhs)
{
    Exp *e = malloc(sizeof(Exp));
    e->Line = yylineno;
    e->Token = token;
    e->Val.Binary.Lhs = lhs;
    e->Val.Binary.Rhs = rhs;
    return e;
}
