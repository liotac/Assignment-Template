#ifndef CODE_H
#define CODE_H

#include "tree.h"

void ind();

void codePROG(PROG *program, char *file);
void codeDECL(DECL *declarations);
void codeSTMT(STMT *statements);
void codeEXPR(EXPR *expressions);

#endif
