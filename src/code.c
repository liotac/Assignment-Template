#include <stdio.h>
#include <stdbool.h>
#include "symbol.h"
#include "code.h"
#include "tree.h"
#include "error.h"

int idlvl = 0;
FILE *fp;
extern SymbolTable *symboltable;

void idn() { for (int i = 0; i < idlvl; i++) { fprintf(fp,"    "); } }

void codePROG(PROG *p)
{
    fp=fopen("foo.c", "w");
    fprintf(fp, "#include <stdio.h>\n");
    fprintf(fp, "int main () {\n");
    idlvl += 1;

    codeDECL(p->declarations);
    codeSTMT(p->statements);

    idn(); fprintf(fp, "return 0;\n");
    fprintf(fp, "}");
    fclose(fp);
}

void codeDECL(DECL *d)
{
    char *declaredtype;
    if (d) {
        switch (d->type)
        {
            case SEQ:
                codeDECL(d->val.seq.element);
                codeDECL(d->val.seq.list);
                break;
            case DECLARATION:
                switch (d->val.declaration.type)
                {
                    case INT: declaredtype = "int"; break;
                    case FLOAT: declaredtype = "float"; break;
                    case BOOLEAN: declaredtype = "int"; break;
                    case STRING: declaredtype = "string"; break;
                    default: panic(d->lineno, d->val.declaration.identifier, "CODE");
                }
                idn();
                fprintf(fp,"%s %s = ", declaredtype, d->val.declaration.identifier);
                codeEXPR(d->val.declaration.expression);
                fprintf(fp,";\n");
                break;
            default:
                panic(d->lineno, "CODE", "DECL");
        }
    }
}

void codeSTMT(STMT *s)
{
    Symbol *sym;
    char *str;
    if (s) {
        switch (s->type)
        {
            case SEQ:
                codeSTMT(s->val.seq.element);
                codeSTMT(s->val.seq.list);
                break;
            case ASSIGNMENT:
                idn();
                fprintf(fp,"%s = ", s->val.assignment.identifier);
                codeEXPR(s->val.assignment.expression);
                fprintf(fp,";\n");
                break;
            case WHILE:
                idn(); fprintf(fp,"while ("); codeEXPR(s->val.cond.condition); fprintf(fp,") {\n");
                idlvl += 1; codeSTMT(s->val.cond.body); idlvl -= 1;
                idn(); fprintf(fp,"}\n");
                break;
            case IF:
                idn(); fprintf(fp,"if ("); codeEXPR(s->val.cond.condition); fprintf(fp,") {\n");
                idlvl += 1; codeSTMT(s->val.cond.body); idlvl -= 1;
                idn(); fprintf(fp,"}\n");
                break;
            case IFELSE:
                idn(); fprintf(fp,"if ("); codeEXPR(s->val.ifel.condition); fprintf(fp,") {\n");
                idlvl += 1; codeSTMT(s->val.ifel.ifpart); idlvl -= 1;
                idn(); fprintf(fp,"} else {\n");
                idlvl += 1; codeSTMT(s->val.ifel.elsepart); idlvl -= 1;
                idn(); fprintf(fp,"}\n");
                break;
            case PRINT:
                idn();
                fprintf(fp,"printf(");
                switch (s->evaltype)
                {
                    case INT:
                        str = "\"%d\"";
                        break;
                    case FLOAT:
                        str = "\"%f\"";
                        break;
                    case STRING:
                        str = "\"%s\"";
                        break;
                    case BOOLEAN:
                        str = "\"%d\"";
                        break;
                    default:
                        break;
                }
                fprintf(fp,"%s,", str);
                codeEXPR(s->val.printexpr);
                fprintf(fp,");\n");
                break;
            case READ:
                idn();
                sym = getSymbol(symboltable, s->val.identifier); 
                switch (sym->type)
                {
                    case INT:
                        str = "\"%d\"";
                        break;
                    case FLOAT:
                        str = "\"%f\"";
                        break;
                    case STRING:
                        str = "\"%s\"";
                        break;
                    case BOOLEAN:
                        str = "\"%d\"";
                        break;
                    default:
                        break;
                }
                fprintf(fp,"scanf(%s,%s);\n", str, s->val.identifier);
                break;
            default:
                panic(s->lineno, "CODE", "STMT");
        }
    }
}

void codeEXPR(EXPR *e)
{
    switch (e->type)
    {
        case IDENT:
            fprintf(fp,"%s", e->val.identifier);
            break;
        case STRING:
            fprintf(fp,"%s", e->val.sval);
            break;
        case INT:
            fprintf(fp,"%d", e->val.ival);
            break;
        case BOOLEAN:
            fprintf(fp,"%d", e->val.bval);
            break;
        case FLOAT:
            fprintf(fp,"%f", e->val.fval);
            break;
        case OR:
            fprintf(fp,"(");
            codeEXPR(e->val.binary.left);
            fprintf(fp,"||");
            codeEXPR(e->val.binary.right);
            fprintf(fp,")");
            break;
        case AND:
            fprintf(fp,"(");
            codeEXPR(e->val.binary.left);
            fprintf(fp,"&&");
            codeEXPR(e->val.binary.right);
            fprintf(fp,")");
            break;
        case EQL:
            fprintf(fp,"(");
            codeEXPR(e->val.binary.left);
            fprintf(fp,"==");
            codeEXPR(e->val.binary.right);
            fprintf(fp,")");
            break;
        case NEQ:
            fprintf(fp,"(");
            codeEXPR(e->val.binary.left);
            fprintf(fp,"!=");
            codeEXPR(e->val.binary.right);
            fprintf(fp,")");
            break;
        case ADD:
            fprintf(fp,"(");
            codeEXPR(e->val.binary.left);
            fprintf(fp,"+");
            codeEXPR(e->val.binary.right);
            fprintf(fp,")");
            break;
        case SUB:
            fprintf(fp,"(");
            codeEXPR(e->val.binary.left);
            fprintf(fp,"-");
            codeEXPR(e->val.binary.right);
            fprintf(fp,")");
            break;
        case MUL:
            fprintf(fp,"(");
            codeEXPR(e->val.binary.left);
            fprintf(fp,"*");
            codeEXPR(e->val.binary.right);
            fprintf(fp,")");
            break;
        case DIV:
            fprintf(fp,"(");
            codeEXPR(e->val.binary.left);
            fprintf(fp,"/");
            codeEXPR(e->val.binary.right);
            fprintf(fp,")");
            break;
        case NEG:
            fprintf(fp,"-(");
            codeEXPR(e->val.unary);
            fprintf(fp,")");
            break;
        case NOT:
            fprintf(fp,"!(");
            codeEXPR(e->val.unary);
            fprintf(fp,")");
            break;
        default:
            panic(e->lineno, "CODE", "EXPR");
    }
}
