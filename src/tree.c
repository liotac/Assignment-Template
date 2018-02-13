#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"
#include "memory.h"

PROG *newPROG(int lineno, DECL *declarations, STMT *statements)
{ PROG *p;
    p = NEW(PROG);
    p->lineno = lineno;
    p->declarations = declarations;
    p->statements = statements;
    return p;
}


DECL *newDECLdeclaration(int lineno, char *identifier, EXPR *expression, Type type)
{ DECL *d;
    d = NEW(DECL);
    d->lineno = lineno;
    d->type = DECLARATION;
    d->val.declaration.identifier = identifier;
    d->val.declaration.expression = expression;
    d->val.declaration.type = type;
    return d;
}

DECL *newDECLseq(int lineno, DECL *element, DECL *list)
{ DECL *d;
    d = NEW(DECL);
    d->lineno = lineno;
    d->type = SEQ;
    d->val.seq.element = element;
    d->val.seq.list = list;
    return d;
}


STMT *newSTMTassignment(int lineno, char *identifier, EXPR *expression)
{ STMT *s;
    s = NEW(STMT);
    s->lineno = lineno;
    s->type = ASSIGNMENT;
    s->val.assignment.identifier = identifier;
    s->val.assignment.expression = expression;
    return s;
}

STMT *newSTMTseq(int lineno, STMT *element, STMT *list)
{ STMT *s;
    s = NEW(STMT);
    s->lineno = lineno;
    s->type = SEQ;
    s->val.seq.element = element;
    s->val.seq.list = list;
    return s;
}

STMT *newSTMTif(int lineno, EXPR *condition, STMT *body)
{ STMT *s;
    s = NEW(STMT);
    s->lineno = lineno;
    s->type = IF;
    s->val.cond.condition = condition;
    s->val.cond.body = body;
    return s;
}

STMT *newSTMTwhile(int lineno, EXPR *condition, STMT *body)
{ STMT *s;
    s = NEW(STMT);
    s->lineno = lineno;
    s->type = WHILE;
    s->val.cond.condition = condition;
    s->val.cond.body = body;
    return s;
}

STMT *newSTMTifel(int lineno, EXPR *condition, STMT *ifpart, STMT *elsepart)
{ STMT *s;
    s = NEW(STMT);
    s->lineno = lineno;
    s->type = IFELSE;
    s->val.ifel.condition = condition;
    s->val.ifel.ifpart = ifpart;
    s->val.ifel.elsepart = elsepart;
    return s;
}

STMT *newSTMTread(int lineno, char *identifier)
{ STMT *s;
    s = NEW(STMT);
    s->lineno = lineno;
    s->type = READ;
    s->val.identifier = identifier;
    return s;
}

STMT *newSTMTprint(int lineno, EXPR *printexpr)
{ STMT *s;
    s = NEW(STMT);
    s->lineno = lineno;
    s->type = PRINT;
    s->val.printexpr = printexpr;
    return s;
}

EXPR *newEXPRidentifier(int lineno, char *identifier)
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
    e->val.sval = stringLiteral;
    return e;
}

EXPR *newEXPRint(int lineno, int intLiteral)
{ EXPR *e;
    e = NEW(EXPR);
    e->lineno = lineno;
    e->type = INT;
    e->val.ival= intLiteral;
    return e;
}

EXPR *newEXPRfloat(int lineno, float floatLiteral)
{ EXPR *e;
    e = NEW(EXPR);
    e->lineno = lineno;
    e->type = FLOAT;
    e->val.fval = floatLiteral;
    return e;
}

EXPR *newEXPRbool(int lineno, bool boolLiteral)
{ EXPR *e;
    e = NEW(EXPR);
    e->lineno = lineno;
    e->type = BOOLEAN;
    e->val.bval = boolLiteral;
    return e;
}

EXPR *newEXPRunary(int lineno, Type type, EXPR *unaryExpression)
{ EXPR *e;
    e = NEW(EXPR);
    e->lineno = lineno;
    e->type = type;
    e->val.unary = unaryExpression;
    return e;
}

EXPR *newEXPRbinary(int lineno, Type type, EXPR *leftExpression, EXPR *rightExpression)
{ EXPR *e;
    e = NEW(EXPR);
    e->lineno = lineno;
    e->type = type;
    e->val.binary.left = leftExpression;
    e->val.binary.right = rightExpression;
    return e;
}
