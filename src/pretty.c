#include <stdio.h>
#include <stdbool.h>
#include "pretty.h"
#include "tree.h"
#include "error.h"

int indentLevel = 0;

void indent() { for (int i = 0; i < indentLevel; i++) { printf("    "); } }

void prettyPROG(PROG *p)
{
    prettyDECL(p->declarations);
    prettySTMT(p->statements);
}

void prettyDECL(DECL *d)
{
    char *declaredtype;
    if (d) {
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
                    case BOOLEAN: declaredtype = "boolean"; break;
                    case STRING: declaredtype = "string"; break;
                    default: panic(d->lineno, d->val.declaration.identifier, "PRETTY");
                }
                printf("var %s : %s = ", d->val.declaration.identifier, declaredtype);
                prettyEXPR(d->val.declaration.expression);
                printf(";\n");
                break;
            default:
                panic(d->lineno, "PRETTY", "DECL");
        }
    }
}

void prettySTMT(STMT *s)
{
    if (s) {
        switch (s->type)
        {
            case SEQ:
                prettySTMT(s->val.seq.element);
                prettySTMT(s->val.seq.list);
                break;
            case ASSIGNMENT:
                indent();
                printf("%s = ", s->val.assignment.identifier);
                prettyEXPR(s->val.assignment.expression);
                printf(";\n");
                break;
            case WHILE:
                indent(); printf("while "); prettyEXPR(s->val.cond.condition); printf(" {\n");
                indentLevel += 1; prettySTMT(s->val.cond.body); indentLevel -= 1;
                indent(); printf("}\n");
                break;
            case IF:
                indent(); printf("if "); prettyEXPR(s->val.cond.condition); printf(" {\n");
                indentLevel += 1; prettySTMT(s->val.cond.body); indentLevel -= 1;
                indent(); printf("}\n");
                break;
            case IFELSE:
                indent(); printf("if "); prettyEXPR(s->val.ifel.condition); printf(" {\n");
                indentLevel += 1; prettySTMT(s->val.ifel.ifpart); indentLevel -= 1;
                indent(); printf("} else {\n");
                indentLevel += 1; prettySTMT(s->val.ifel.elsepart); indentLevel -= 1;
                indent(); printf("}\n");
                break;
            case PRINT:
                indent();
                printf("print ");
                prettyEXPR(s->val.printexpr);
                printf(";\n");
                break;
            case READ:
                indent();
                printf("read %s;\n", s->val.identifier);
                break;
            default:
                panic(s->lineno, "PRETTY", "STMT");
        }
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
            panic(e->lineno, "PRETTY", "EXPR");
    }
}
