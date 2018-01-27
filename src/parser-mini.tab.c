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

#ifndef YY_YY_PARSER_MINI_TAB_C_INCLUDED
# define YY_YY_PARSER_MINI_TAB_C_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    tINT = 258,
    tFLOAT = 259,
    tSTRING = 260,
    tBOOLEAN = 261,
    tIDENTIFIER = 262,
    ADD = 263,
    SUB = 264,
    MUL = 265,
    DIV = 266,
    VAR = 267,
    INT = 268,
    FLOAT = 269,
    BOOLEAN = 270,
    STRING = 271,
    LPAREN = 272,
    RPAREN = 273,
    IF = 274,
    ELSE = 275,
    WHILE = 276,
    LBRACE = 277,
    RBRACE = 278,
    NOT = 279,
    NEQ = 280,
    EQL = 281,
    AND = 282,
    OR = 283,
    ASSIGN = 284,
    COLON = 285,
    SEMICOLON = 286,
    PRINT = 287,
    READ = 288,
    UMINUS = 289
  };
#endif
/* Tokens.  */
#define tINT 258
#define tFLOAT 259
#define tSTRING 260
#define tBOOLEAN 261
#define tIDENTIFIER 262
#define ADD 263
#define SUB 264
#define MUL 265
#define DIV 266
#define VAR 267
#define INT 268
#define FLOAT 269
#define BOOLEAN 270
#define STRING 271
#define LPAREN 272
#define RPAREN 273
#define IF 274
#define ELSE 275
#define WHILE 276
#define LBRACE 277
#define RBRACE 278
#define NOT 279
#define NEQ 280
#define EQL 281
#define AND 282
#define OR 283
#define ASSIGN 284
#define COLON 285
#define SEMICOLON 286
#define PRINT 287
#define READ 288
#define UMINUS 289

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 13 "parser-mini.y" /* yacc.c:1909  */

    int intval;
    char *strval;
    double fltval;
    int booval;

#line 129 "parser-mini.tab.c" /* yacc.c:1909  */
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

#endif /* !YY_YY_PARSER_MINI_TAB_C_INCLUDED  */
