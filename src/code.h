#ifndef CODE_H
#define CODE_H

#include "tree.h"

void ind();

void codePROG(PROG *program);
void codeDECL(DECL *declarations);
void codeSTMT(STMT *statements);
void codeEXPR(EXPR *expressions);

#endif
