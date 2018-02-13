#ifndef PRETTY_H
#define PRETTY_H

#include "tree.h"

int indentLevel = 0;

void prettyPROG(PROG *program);
void prettyDECL(DECL *declarations);
void prettySTMT(STMT *statements);
void prettyEXPR(EXPR *expressions);

#endif
