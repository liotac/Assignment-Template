// Expression Tokens
typedef enum {
    tIDENT;
    tSTRING;
    stringlit;
    tINT;
    tBOOLEAN;
    intlit;
    tFLOAT;
    floatlit;
    binaryop;
    OR;
    AND;
    EQL;
    NEQ;
    ADD;
    SUB;
    MUL;
    DIV;
    unaryop;
    NEG;
    NOT;
} TokenType;

// ----------------------------------------------------------------------------
// Node structures definitions

// exp_s is an Expression Node
typedef struct Exp {
    int Line;
    TokenType Token ;
    union {
        char *String;
        int Int;
        double Float;
        struct {
            Exp *Lhs;
            Exp *Rhs;
        } Binary;
        Exp *Unary;
    } Val;
} Exp;

Exp *NewExpUnary(TokenType token, void *value);
Exp *NewExpBinary(TokenType token, Exp *lhs, Exp *rhs);
