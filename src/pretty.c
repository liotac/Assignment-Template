#include <stdio.h>
#include <stdbool.h>
#include "pretty.h"
#include "tree.h"
#include "error.h"

void prettyPROG(PROG *p)
{
    prettyDECL(p->declarations);
    prettySTMT(p->statements);
}

void prettyDECL(DECL *d)
{
    char *declaredtype;
    switch (d->type)
    {
        case SEQ:
            prettyDECL(d->val.seq.element);
            prettyDECL(d->val.seq.list);
            break;
        case DECLARATION:
            switch (d->val.declaration.type)
            {
                case INT: declaredtype = "int"; break;
                case FLOAT: declaredtype = "float"; break;
                case FLOAT: declaredtype = "boolean"; break;
                case STRING: declaredtype = "string"; break;
                default: panic(d->lineno, d->val.declaration.identifier, "PRETTY");
            }
            printf("var %s : %s = ", d->val.declaration.identifier, declaredtype);
            prettyEXPR(d->val.declaration.expression);
            printf(";\n");
            break
        default:
            panic(d->lineno, "PRETTY", "DECL");
    }
}

void prettySTMT(STMT *s)
{
    switch (s->type)
    {
        case SEQ:
            prettySTMT(s->val.seq.element);
            prettySTMT(s->val.seq.list);
            break;
        case ASSIGNMENT:
            printf("%s = ", s->val.assignment.identifier);
            prettyEXPR(s->val.assignment.expression);
            printf(";\n");
            break;
        case WHILE:
            printf("while ");
            prettyEXPR(s->val.cond.condition);
            prettySTMT(s->val.cond.body);
            printf(" {\n");
            printf("\n}\n");
            break;
        case IF:
            printf("if ");
            prettyEXPR(s->val.cond.condition);
            prettySTMT(s->val.cond.body);
            printf(" {\n");
            printf("\n}\n");
            break;
        case IFEL:
            printf("if ");
            prettyEXPR(s->val.ifel.condition);
            printf(" {\n");
            prettySTMT(s->val.ifel.ifpart);
            printf("\n} else {\n");
            prettySTMT(s->val.ifel.elsepart);
            printf("\n}\n");
            break;
        case PRINT:
            printf("print ");
            prettyEXPR(s->val.printexpr);
            printf(";\n");
            break;
        case READ:
            printf("read %s;\n", s->val.identifier);
            break;
        default:
            panic(d->lineno, "PRETTY", "STMT");
    }
}

void prettyEXPR(EXPR *e)
{
    switch (e->type)
    {
        case IDENT:
            printf("%s", e->val.identifier);
            break;
        case STRING:
            printf("%s", e->val.sval);
            break;
        case INT:
            printf("%d", e->val.ival);
            break;
        case BOOLEAN:
            printf("%d", e->val.bval);
            break;
        case FLOAT:
            printf("%f", e->val.fval);
            break;
        case OR:
            printf("(");
            prettyEXPR(e->val.binary.left);
            printf("||");
            prettyEXPR(e->val.binary.right);
            printf(")");
            break;
        case AND:
            printf("(");
            prettyEXPR(e->val.binary.left);
            printf("&&");
            prettyEXPR(e->val.binary.right);
            printf(")");
            break;
        case EQL:
            printf("(");
            prettyEXPR(e->val.binary.left);
            printf("==");
            prettyEXPR(e->val.binary.right);
            printf(")");
            break;
        case NEQ:
            printf("(");
            prettyEXPR(e->val.binary.left);
            printf("!=");
            prettyEXPR(e->val.binary.right);
            printf(")");
            break;
        case ADD:
            printf("(");
            prettyEXPR(e->val.binary.left);
            printf("+");
            prettyEXPR(e->val.binary.right);
            printf(")");
            break;
        case SUB:
            printf("(");
            prettyEXPR(e->val.binary.left);
            printf("-");
            prettyEXPR(e->val.binary.right);
            printf(")");
            break;
        case MUL:
            printf("(");
            prettyEXPR(e->val.binary.left);
            printf("*");
            prettyEXPR(e->val.binary.right);
            printf(")");
            break;
        case DIV:
            printf("(");
            prettyEXPR(e->val.binary.left);
            printf("/");
            prettyEXPR(e->val.binary.right);
            printf(")");
            break;
        case NEG:
            printf("-(");
            prettyEXPR(e->val.unary);
            printf(")");
            break;
        case NOT:
            printf("!(");
            prettyEXPR(e->val.unary);
            printf(")");
            break;
        default:
            panic(d->lineno, "PRETTY", "EXPR");
    }
}

