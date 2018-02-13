/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_TAB_C_INCLUDED
# define YY_YY_PARSER_TAB_C_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 22 "parser.y" /* yacc.c:1909  */

    #include "tree.h"
    #include <stdbool.h>

#line 49 "parser.tab.c" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    btINT = 258,
    btFLOAT = 259,
    btSTRING = 260,
    btBOOLEAN = 261,
    btIDENT = 262,
    bADD = 263,
    bSUB = 264,
    bMUL = 265,
    bDIV = 266,
    bNOT = 267,
    bNEQ = 268,
    bEQL = 269,
    bAND = 270,
    bOR = 271,
    bASSIGN = 272,
    bVAR = 273,
    bCOLON = 274,
    bSEMICOLON = 275,
    bLBRACE = 276,
    bRBRACE = 277,
    bPRINT = 278,
    bREAD = 279,
    bLPAREN = 280,
    bRPAREN = 281,
    bIF = 282,
    bELSE = 283,
    bWHILE = 284,
    bINT = 285,
    bFLOAT = 286,
    bBOOLEAN = 287,
    bSTRING = 288,
    bUMINUS = 289
  };
#endif
/* Tokens.  */
#define btINT 258
#define btFLOAT 259
#define btSTRING 260
#define btBOOLEAN 261
#define btIDENT 262
#define bADD 263
#define bSUB 264
#define bMUL 265
#define bDIV 266
#define bNOT 267
#define bNEQ 268
#define bEQL 269
#define bAND 270
#define bOR 271
#define bASSIGN 272
#define bVAR 273
#define bCOLON 274
#define bSEMICOLON 275
#define bLBRACE 276
#define bRBRACE 277
#define bPRINT 278
#define bREAD 279
#define bLPAREN 280
#define bRPAREN 281
#define bIF 282
#define bELSE 283
#define bWHILE 284
#define bINT 285
#define bFLOAT 286
#define bBOOLEAN 287
#define bSTRING 288
#define bUMINUS 289

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 27 "parser.y" /* yacc.c:1909  */

    int ival;
    float fval;
    bool bval;
    char *sval;
    char *identifier;
    PROG *prog;
    DECL *decl;
    STMT *stmt;
    EXPR *expr;

#line 141 "parser.tab.c" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_C_INCLUDED  */
