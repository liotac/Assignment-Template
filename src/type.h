#include "symbol.h"
#include "tree.h"

void typePROG(SymbolTable *t, PROG *program);
void typeDECL(SymbolTable *t, DECL *declarations);
void typeSTMT(SymbolTable *t, STMT *statements);
int typeEXPR(SymbolTable *t, EXPR *expressions);
