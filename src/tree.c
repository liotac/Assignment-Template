#include <stdlib.h>
#include <boollib.h>
#include "tree.h"
#include "memory.h"

PROG *newPROG(int lineno, DECL *declarations, STMT *statements)
{ PROGRAM *p
    p = NEW(PROG);
    p->lineno = lineno;
    p->val.declarations = declarations;
    p->val.statements = statements;
    return p;
}


DECL *newDECLdeclaration(int lineno, SYMBOL *identifier, ExprType type, EXPR *expression)
{ DECL *d;
    d = NEW(DECL);
    d->lineno = lineno;
    d->type = DECLARE;
    d->val.identifier = identifier;
    d->val.type = type;
    d->val.expression = expression;
    return d;
}

DECL *newDECLseq(int lineno, DECL *element, DECL *list)
{ DECL *d;
    d = NEW(DECL);
    d->lineno = lineno;
    d->type = SEQ;
    d->val.element = element
    d->val.list = list;
    return d;
}


STMT *newSTMTassignment(int lineno, SYMBOL *identifier, EXPR *expression)
{ STMT *s;
    s = NEW(STMT);
    s->lineno = lineno;
    s->type = ASSIGN;
    s->val.identifier = identifier;
    s->val.expression = expression;
    return s;
}

STMT *newSTMTseq(int lineno, STMT *element, STMT *list)
{ STMT *s;
    s = NEW(STMT);
    s->lineno = lineno;
    s->type = SEQ;
    s->val.element = element;
    s->val.list = list;
    return s;
}

STMT *newSTMTif(int lineno, EXPR *condition, STMT *body)
{ STMT *s;
    s = NEW(STMT);
    s->lineno = lineno;
    s->type = IF;
    s->val.condition = condition;
    s->val.body = body;
    return s;
}

STMT *newSTMTwhile(int lineno, EXPR *condition, STMT *body)
{ STMT *s;
    s = NEW(STMT);
    s->lineno = lineno;
    s->type = WHILE;
    s->val.condition = condition;
    s->val.body = body;
    return s;
}

STMT *newSTMTifel(int lineno, EXPR *condition, STMT *ifpart, STMT *elsepart)
{ STMT *s;
    s = NEW(STMT);
    s->lineno = lineno;
    s->type = IFELSE;
    s->val.condition = condition;
    s->val.ifpart = ifpart;
    s->val.elsepart = elsepart;
    return s;
}

STMT *newSTMTread(int lineno, EXPR *rdpr)
{ STMT *s;
    s = NEW(STMT);
    s->lineno = lineno;
    s->type = READ;
    s->val.rdpr = rdpr;
    return s;
}

STMT *newSTMTprint(int lineno, EXPR *rdpr)
{ STMT *s;
    s = NEW(STMT);
    s->lineno = lineno;
    s->type = PRINT;
    s->val.rdpr = rdpr;
    return s;
}

EXPR *newEXPRidentifier(int lineno, SYMBOL *identifier)
{ EXPR *e;
    e = NEW(EXPR);
    e->lineno = lineno;
    e->type = IDENT;
    e->val.identifier = identifier;
    return e;
}

EXPR *newEXPRstring(int lineno, char *stringLiteral)
{ EXPR *e;
    e = NEW(EXPR);
    e->lineno = lineno;
    e->type = STRING;
    e->val.sLit = stringLiteral;
    return e;
}

EXPR *newEXPRint(int lineno, int *intLiteral)
{ EXPR *e;
    e = NEW(EXPR);
    e->lineno = lineno;
    e->type = INT;
    e->val.iLit = intLiteral;
    return e;
}

EXPR *newEXPRfloat(int lineno, float *floatLiteral)
{ EXPR *e;
    e = NEW(EXPR);
    e->lineno = lineno;
    e->type = FLOAT;
    e->val.fLit = floatLiteral;
    return e;
}

EXPR *newEXPRbool(int lineno, bool *boolLiteral)
{ EXPR *e;
    e = NEW(EXPR);
    e->lineno = lineno;
    e->type = BOOL;
    e->val.bLit = boolLiteral;
    return e;
}

EXPR *newEXPRunary(int lineno, ExprType type, EXPR *unaryExpression)
{ EXPR *e;
    e = NEW(EXPR);
    e->lineno = lineno;
    e->type = type;
    e->val.unary = unaryExpression;
    return e;
}

EXPR *newEXPRbinary(int lineno, ExprType type, EXPR *leftExpression, EXPR *rightExpression)
{ EXPR *e;
    e = NEW(EXPR);
    e->lineno = lineno;
    e->type = type;
    e->val.left = leftExpression;
    e->val.right = rightExpression;
    return e;
}
