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

#ifndef YY_YY_SPL_TAB_H_INCLUDED
# define YY_YY_SPL_TAB_H_INCLUDED
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
    T_LP = 258,
    T_RP = 259,
    T_LB = 260,
    T_RB = 261,
    T_DOT = 262,
    T_COMMA = 263,
    T_COLON = 264,
    T_PLUS = 265,
    T_MINUS = 266,
    T_MUL = 267,
    T_DIV = 268,
    T_GT = 269,
    T_LT = 270,
    T_EQUAL = 271,
    T_NE = 272,
    T_LE = 273,
    T_GE = 274,
    T_ASSIGN = 275,
    T_NOT = 276,
    T_MOD = 277,
    T_DOTDOT = 278,
    T_SEMI = 279,
    T_AND = 280,
    T_ARRAY = 281,
    T_BEGIN = 282,
    T_CASE = 283,
    T_CONST = 284,
    T_DO = 285,
    T_DOWNTO = 286,
    T_ELSE = 287,
    T_END = 288,
    T_FOR = 289,
    T_FUNCTION = 290,
    T_GOTO = 291,
    T_IF = 292,
    T_IN = 293,
    T_OF = 294,
    T_OR = 295,
    T_PACKED = 296,
    T_PROCEDURE = 297,
    T_PROGRAM = 298,
    T_RECORD = 299,
    T_REPEAT = 300,
    T_SET = 301,
    T_THEN = 302,
    T_TO = 303,
    T_TYPE = 304,
    T_UNTIL = 305,
    T_VAR = 306,
    T_WHILE = 307,
    T_WITH = 308,
    T_ABS = 309,
    T_CHR = 310,
    T_ODD = 311,
    T_ORD = 312,
    T_PRED = 313,
    T_SQR = 314,
    T_SQRT = 315,
    T_SUCC = 316,
    T_WRITE = 317,
    T_WRITELN = 318,
    T_READ = 319,
    T_BOOLEAN = 320,
    T_CHAR = 321,
    T_INTEGER = 322,
    T_REAL = 323,
    T_STR = 324,
    T_TRUE = 325,
    T_FALSE = 326,
    T_MAXINT = 327,
    S_ID = 328,
    S_INTEGER = 329,
    S_REAL = 330,
    S_CHAR = 331,
    S_STRING = 332
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 35 "spl.y" /* yacc.c:1909  */

    int iVal;
    cst_tree tVal;

#line 137 "spl.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SPL_TAB_H_INCLUDED  */
