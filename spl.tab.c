/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "spl.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cst.h"
#include "symtab.h"
#include "common.h"
#include "tree.h"
#include "translator.h"

#define NOTHING -1

extern "C" int yylex(void);
extern "C" FILE* yyin;

int currentSymTabSize = 0;
sym_tab_node symtab[SYM_TAB_LEN];

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}


#line 91 "spl.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "spl.tab.h".  */
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
#line 35 "spl.y" /* yacc.c:355  */

    int iVal;
    cst_tree tVal;

#line 214 "spl.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SPL_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 231 "spl.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   380

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  151
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  289

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   333

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    56,    56,    64,    68,    74,    77,    81,    86,    91,
      96,   101,   105,   109,   114,   119,   123,   127,   132,   136,
     140,   144,   148,   153,   157,   161,   166,   171,   175,   179,
     184,   189,   193,   197,   202,   206,   210,   214,   218,   223,
     227,   231,   235,   239,   244,   250,   257,   262,   267,   271,
     276,   281,   285,   290,   295,   299,   303,   308,   313,   317,
     321,   325,   329,   334,   339,   344,   349,   354,   359,   363,
     367,   372,   376,   381,   386,   391,   396,   401,   406,   410,
     414,   419,   423,   427,   431,   435,   439,   443,   447,   451,
     456,   460,   464,   470,   474,   478,   482,   487,   491,   495,
     500,   505,   509,   514,   519,   524,   529,   533,   538,   543,
     547,   552,   556,   561,   566,   570,   575,   579,   583,   587,
     591,   595,   599,   604,   608,   612,   616,   621,   625,   629,
     633,   637,   642,   646,   650,   654,   658,   662,   666,   670,
     676,   680,   684,   688,   692,   696,   700,   704,   708,   712,
     718,   722
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_LP", "T_RP", "T_LB", "T_RB", "T_DOT",
  "T_COMMA", "T_COLON", "T_PLUS", "T_MINUS", "T_MUL", "T_DIV", "T_GT",
  "T_LT", "T_EQUAL", "T_NE", "T_LE", "T_GE", "T_ASSIGN", "T_NOT", "T_MOD",
  "T_DOTDOT", "T_SEMI", "T_AND", "T_ARRAY", "T_BEGIN", "T_CASE", "T_CONST",
  "T_DO", "T_DOWNTO", "T_ELSE", "T_END", "T_FOR", "T_FUNCTION", "T_GOTO",
  "T_IF", "T_IN", "T_OF", "T_OR", "T_PACKED", "T_PROCEDURE", "T_PROGRAM",
  "T_RECORD", "T_REPEAT", "T_SET", "T_THEN", "T_TO", "T_TYPE", "T_UNTIL",
  "T_VAR", "T_WHILE", "T_WITH", "T_ABS", "T_CHR", "T_ODD", "T_ORD",
  "T_PRED", "T_SQR", "T_SQRT", "T_SUCC", "T_WRITE", "T_WRITELN", "T_READ",
  "T_BOOLEAN", "T_CHAR", "T_INTEGER", "T_REAL", "T_STR", "T_TRUE",
  "T_FALSE", "T_MAXINT", "S_ID", "S_INTEGER", "S_REAL", "S_CHAR",
  "S_STRING", "\"then\"", "$accept", "program", "program_head",
  "program_head_para", "routine", "sub_routine", "routine_head",
  "label_part", "label_list", "const_part", "const_expr_list",
  "const_value", "sys_con", "type_part", "type_decl_list",
  "type_definition", "type_decl", "sys_type", "simple_type_decl",
  "array_type_decl", "record_type_decl", "field_decl_list", "field_decl",
  "name_list", "var_part", "var_decl_list", "var_decl", "routine_part",
  "function_decl", "function_head", "procedure_decl", "procedure_head",
  "parameters", "para_decl_list", "para_type_list", "var_para_list",
  "val_para_list", "routine_body", "compound_stmt", "stmt_list", "stmt",
  "non_label_stmt", "assign_stmt", "proc_stmt", "sys_proc", "if_stmt",
  "else_clause", "repeat_stmt", "while_stmt", "for_stmt", "direction",
  "case_stmt", "case_expr_list", "case_expr", "goto_stmt",
  "expression_list", "expression", "expr", "term", "sys_funct", "factor",
  "args_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333
};
# endif

#define YYPACT_NINF -201

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-201)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -32,   -56,    20,   -51,    15,  -201,  -201,    61,    17,    48,
      72,    18,  -201,  -201,  -201,  -201,  -201,    40,    81,    62,
    -201,    37,   -12,   133,    84,    85,   109,  -201,   139,    92,
      67,  -201,    96,    98,    67,  -201,    67,  -201,  -201,  -201,
      78,   157,  -201,   149,  -201,  -201,  -201,   171,  -201,  -201,
    -201,  -201,  -201,  -201,   212,   161,   166,    85,  -201,   111,
      47,  -201,  -201,    67,    67,    67,  -201,  -201,  -201,  -201,
    -201,  -201,  -201,  -201,  -201,  -201,  -201,    97,  -201,  -201,
    -201,  -201,  -201,  -201,   185,    53,   107,   180,  -201,   165,
    -201,    39,   229,   302,    67,    67,   114,    67,   134,  -201,
      67,   168,   212,   164,  -201,  -201,    57,   111,  -201,   115,
     120,    47,  -201,   170,  -201,   182,   325,  -201,  -201,    67,
      67,   137,    67,    67,    67,    67,    67,    67,   295,    67,
      67,    67,    67,    67,    67,    67,    67,    67,   233,    67,
     233,   338,    38,   331,   191,   338,  -201,    86,   338,   208,
    -201,   192,   111,   212,   210,   111,  -201,  -201,  -201,  -201,
    -201,   194,   195,   196,  -201,  -201,  -201,  -201,   150,   164,
    -201,   222,   222,  -201,  -201,   -51,   -51,  -201,    93,   345,
    -201,    53,    53,    53,    53,    53,    53,   217,   218,   238,
    -201,   107,   107,   107,  -201,  -201,  -201,  -201,   108,    12,
     226,   338,  -201,  -201,    67,   239,    67,  -201,    67,  -201,
    -201,   110,   219,   178,   -26,  -201,   125,   189,   212,  -201,
    -201,   240,   -41,   259,  -201,   248,    17,   249,  -201,  -201,
     233,   233,  -201,  -201,  -201,  -201,  -201,    67,   233,  -201,
     338,    67,   338,   338,  -201,    76,   269,  -201,  -201,   164,
    -201,  -201,  -201,   111,   268,    10,  -201,   271,   281,   178,
    -201,  -201,  -201,   253,   270,   308,  -201,   338,   212,  -201,
     260,   274,   268,  -201,   -41,   178,   178,  -201,  -201,  -201,
     233,  -201,   164,  -201,  -201,  -201,  -201,  -201,  -201
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    11,     0,     1,    13,     0,     0,    15,
      10,     0,     3,     2,    78,     7,    75,     0,    27,     0,
       6,     0,     0,     0,    14,     0,    54,    12,     0,     0,
       0,    76,     0,     0,     0,    78,     0,    97,    98,    99,
      93,     0,    83,     0,    80,    81,    82,     0,    84,    85,
      86,    87,    88,    89,     0,     0,     0,    26,    29,     0,
      62,     4,     5,     0,     0,     0,   132,   133,   134,   135,
     136,   137,   138,   139,    23,    24,    25,   140,    18,    19,
      20,    21,   144,    22,     0,   122,   126,   142,   131,     0,
     113,     0,     0,     0,     0,     0,     0,     0,     0,    77,
       0,     0,     0,     0,    28,    52,     0,    53,    56,     0,
       0,     9,    60,     0,    61,     0,     0,   147,   146,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   151,     0,     0,     0,    90,    79,     0,   115,   131,
      17,     0,     0,     0,     0,     0,    37,    34,    35,    36,
      38,    40,     0,     0,    39,    31,    32,    33,     0,     0,
      55,    68,    68,    58,    59,    11,    11,   145,     0,     0,
     149,   117,   119,   120,   121,   118,   116,     0,     0,     0,
     110,   123,   124,   125,   127,   128,   129,   130,     0,     0,
     102,   103,   104,    94,     0,     0,     0,    95,     0,    96,
      16,     0,     0,     0,     0,    49,     0,     0,     0,    30,
      51,     0,     0,     0,    66,     0,     0,     0,   141,   148,
       0,     0,   108,   109,   143,   107,   106,     0,     0,   100,
     150,     0,    92,   114,    41,     0,     0,    47,    48,     0,
      45,    42,    57,     0,    74,     0,    70,     0,     0,     0,
      63,     8,    65,     0,     0,     0,   101,    91,     0,    43,
       0,     0,    73,    67,     0,     0,     0,    64,   112,   111,
       0,    44,     0,    50,    69,    71,    72,   105,    46
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -201,  -201,  -201,  -201,  -201,   124,   298,  -201,  -201,  -201,
    -201,   -54,  -201,  -201,  -201,   247,  -165,  -201,  -200,  -201,
    -201,  -201,    91,  -143,  -201,  -201,   221,  -201,   220,  -201,
     223,  -201,   158,  -201,    59,  -201,  -201,   132,    -7,   300,
    -135,   282,  -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,
    -201,  -201,  -201,   147,  -201,  -201,   -28,   251,    25,  -201,
     -27,  -100
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    21,     7,   225,   226,     9,    10,    18,
      24,    82,    83,    26,    57,    58,   163,   164,   165,   166,
     167,   214,   215,   106,    60,   107,   108,   111,   112,   113,
     114,   115,   223,   255,   256,   257,   258,    15,    42,    22,
      43,    44,    45,    46,    47,    48,   239,    49,    50,    51,
     237,    52,   189,   190,    53,   147,   141,    85,    86,    87,
      88,   142
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
     101,    16,    84,   200,   221,   202,    91,   247,    93,   211,
     253,     1,   216,   246,   273,    14,    30,     4,    11,   178,
       5,    31,    32,     6,    33,    34,   122,   123,   124,   125,
     126,   127,   105,    35,   274,   116,   198,   117,   118,    12,
      36,    28,   203,   235,    14,    29,   204,   105,   151,   162,
      37,    38,    39,   122,   123,   124,   125,   126,   127,   277,
     236,    40,    41,   129,   130,   168,   169,   143,    13,   145,
      63,   216,   148,   149,   188,   285,   286,    17,    64,   254,
      19,    94,   109,    95,   271,    96,   138,   268,    65,   110,
     207,    20,   179,   131,   208,   263,   264,   228,    97,   212,
     119,   204,   120,   266,   121,   194,   195,   196,   197,   199,
     272,   201,   234,    23,   244,   162,   204,   288,   168,   132,
     133,    66,    67,    68,    69,    70,    71,    72,    73,   134,
      25,   254,   135,   168,   249,   188,    27,    74,    75,    76,
      77,    78,    79,    80,    81,   287,    74,    75,    76,    54,
      78,    79,    80,    81,   191,   192,   193,    55,    56,   162,
      59,    14,    30,    61,   251,    62,    98,   152,    32,    89,
      33,    34,    90,    99,   100,   153,   240,   102,   242,    35,
     243,   152,   103,   136,   105,   137,    36,   144,   171,   153,
     154,   269,   150,   172,   175,   162,    37,    38,    39,   122,
     123,   124,   125,   126,   127,   162,   176,    40,   155,   265,
     180,   206,   209,   267,   281,   213,   210,   217,   218,    16,
     219,   162,   162,   220,   128,   222,   230,   231,   162,   156,
     157,   158,   159,   160,    74,    75,    76,   161,    78,    79,
      80,    81,   245,   156,   157,   158,   159,   160,    74,    75,
      76,   161,    78,    79,    80,    81,    14,    30,   238,   241,
      14,    30,   250,    32,   252,    33,    34,    32,   259,    33,
      34,   232,   260,   262,    35,   270,   168,   278,    35,   139,
     275,    36,    74,    75,    76,    36,    78,    79,    80,    81,
     276,    37,    38,    39,   279,    37,    38,    39,   283,   282,
     227,     8,    40,    41,   104,   248,    40,    41,    74,    75,
      76,   187,    78,    79,    80,    81,   122,   123,   124,   125,
     126,   127,   122,   123,   124,   125,   126,   127,   170,   177,
     224,   173,   140,   284,   174,    92,   233,   205,   280,   122,
     123,   124,   125,   126,   127,   122,   123,   124,   125,   126,
     127,   229,   122,   123,   124,   125,   126,   127,   261,   122,
     123,   124,   125,   126,   127,    74,    75,    76,   187,    78,
      79,    80,    81,   181,   182,   183,   184,   185,   186,     0,
     146
};

static const yytype_int16 yycheck[] =
{
      54,     8,    30,   138,   169,   140,    34,    33,    36,   152,
      51,    43,   155,   213,     4,    27,    28,    73,     3,   119,
       0,    33,    34,    74,    36,    37,    14,    15,    16,    17,
      18,    19,    73,    45,    24,    63,   136,    64,    65,    24,
      52,     4,     4,    31,    27,     8,     8,    73,   102,   103,
      62,    63,    64,    14,    15,    16,    17,    18,    19,   259,
      48,    73,    74,    10,    11,     8,     9,    95,     7,    97,
       3,   214,   100,   100,   128,   275,   276,    29,    11,   222,
       8,     3,    35,     5,   249,     7,    47,    11,    21,    42,
       4,    73,   120,    40,     8,   230,   231,     4,    20,   153,
       3,     8,     5,   238,     7,   132,   133,   134,   135,   137,
     253,   139,     4,    73,     4,   169,     8,   282,     8,    12,
      13,    54,    55,    56,    57,    58,    59,    60,    61,    22,
      49,   274,    25,     8,     9,   189,    74,    70,    71,    72,
      73,    74,    75,    76,    77,   280,    70,    71,    72,    16,
      74,    75,    76,    77,   129,   130,   131,    73,    73,   213,
      51,    27,    28,    24,   218,    73,     9,     3,    34,    73,
      36,    37,    74,    24,     3,    11,   204,    16,   206,    45,
     208,     3,    16,     3,    73,    20,    52,    73,    73,    11,
      26,   245,    24,    73,    24,   249,    62,    63,    64,    14,
      15,    16,    17,    18,    19,   259,    24,    73,    44,   237,
      73,    20,     4,   241,   268,     5,    24,    23,    23,   226,
      24,   275,   276,    73,    39,     3,     9,     9,   282,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    23,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    27,    28,    32,    20,
      27,    28,    73,    34,    24,    36,    37,    34,     9,    36,
      37,    33,    24,    24,    45,     6,     8,    24,    45,    50,
       9,    52,    70,    71,    72,    52,    74,    75,    76,    77,
       9,    62,    63,    64,    24,    62,    63,    64,    24,    39,
     176,     3,    73,    74,    57,   214,    73,    74,    70,    71,
      72,    73,    74,    75,    76,    77,    14,    15,    16,    17,
      18,    19,    14,    15,    16,    17,    18,    19,   107,     4,
     172,   111,    30,   274,   111,    35,   189,     6,    30,    14,
      15,    16,    17,    18,    19,    14,    15,    16,    17,    18,
      19,     6,    14,    15,    16,    17,    18,    19,   226,    14,
      15,    16,    17,    18,    19,    70,    71,    72,    73,    74,
      75,    76,    77,   122,   123,   124,   125,   126,   127,    -1,
      98
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    43,    80,    81,    73,     0,    74,    83,    85,    86,
      87,     3,    24,     7,    27,   116,   117,    29,    88,     8,
      73,    82,   118,    73,    89,    49,    92,    74,     4,     8,
      28,    33,    34,    36,    37,    45,    52,    62,    63,    64,
      73,    74,   117,   119,   120,   121,   122,   123,   124,   126,
     127,   128,   130,   133,    16,    73,    73,    93,    94,    51,
     103,    24,    73,     3,    11,    21,    54,    55,    56,    57,
      58,    59,    60,    61,    70,    71,    72,    73,    74,    75,
      76,    77,    90,    91,   135,   136,   137,   138,   139,    73,
      74,   135,   118,   135,     3,     5,     7,    20,     9,    24,
       3,    90,    16,    16,    94,    73,   102,   104,   105,    35,
      42,   106,   107,   108,   109,   110,   135,   139,   139,     3,
       5,     7,    14,    15,    16,    17,    18,    19,    39,    10,
      11,    40,    12,    13,    22,    25,     3,    20,    47,    50,
      30,   135,   140,   135,    73,   135,   120,   134,   135,   139,
      24,    90,     3,    11,    26,    44,    65,    66,    67,    68,
      69,    73,    90,    95,    96,    97,    98,    99,     8,     9,
     105,    73,    73,   107,   109,    24,    24,     4,   140,   135,
      73,   136,   136,   136,   136,   136,   136,    73,    90,   131,
     132,   137,   137,   137,   139,   139,   139,   139,   140,   135,
     119,   135,   119,     4,     8,     6,    20,     4,     8,     4,
      24,   102,    90,     5,   100,   101,   102,    23,    23,    24,
      73,    95,     3,   111,   111,    84,    85,    84,     4,     6,
       9,     9,    33,   132,     4,    31,    48,   129,    32,   125,
     135,    20,   135,   135,     4,    23,    97,    33,   101,     9,
      73,    90,    24,    51,   102,   112,   113,   114,   115,     9,
      24,   116,    24,   119,   119,   135,   119,   135,    11,    90,
       6,    95,   102,     4,    24,     9,     9,    97,    24,    24,
      30,    90,    39,    24,   113,    97,    97,   119,    95
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    79,    80,    81,    81,    82,    82,    83,    84,    85,
      86,    86,    87,    87,    88,    88,    89,    89,    90,    90,
      90,    90,    90,    91,    91,    91,    92,    92,    93,    93,
      94,    95,    95,    95,    96,    96,    96,    96,    96,    97,
      97,    97,    97,    97,    97,    97,    98,    99,   100,   100,
     101,   102,   102,   103,   103,   104,   104,   105,   106,   106,
     106,   106,   106,   107,   108,   109,   110,   111,   111,   112,
     112,   113,   113,   114,   115,   116,   117,   118,   118,   119,
     119,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     121,   121,   121,   122,   122,   122,   122,   123,   123,   123,
     124,   125,   125,   126,   127,   128,   129,   129,   130,   131,
     131,   132,   132,   133,   134,   134,   135,   135,   135,   135,
     135,   135,   135,   136,   136,   136,   136,   137,   137,   137,
     137,   137,   138,   138,   138,   138,   138,   138,   138,   138,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     140,   140
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     6,     3,     1,     2,     2,     5,
       1,     0,     3,     1,     2,     0,     5,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     0,     2,     1,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     4,     5,     3,     6,     3,     2,     1,
       4,     3,     1,     2,     0,     2,     1,     4,     2,     2,
       1,     1,     0,     4,     5,     4,     3,     3,     0,     3,
       1,     3,     3,     2,     1,     1,     3,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     6,     5,     1,     4,     4,     4,     1,     1,     1,
       5,     2,     0,     4,     4,     8,     1,     1,     5,     2,
       1,     4,     4,     2,     3,     1,     3,     3,     3,     3,
       3,     3,     1,     3,     3,     3,     1,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     1,     4,     1,     3,     2,     2,     4,     3,
       3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 57 "spl.y" /* yacc.c:1646  */
    {
        cst_tree root = create_node(NOTHING, PROGRAM, (yyvsp[-2].tVal), (yyvsp[-1].tVal), NULL, NULL, NULL);
        Base* ast_root = Translator::translate(root);
        //printTree("log", ast_root);
        (yyval.tVal) = root;
    }
#line 1557 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 65 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[-1].iVal), PROGRAM_HEAD, NULL, NULL, NULL, NULL, NULL);
    }
#line 1565 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 69 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[-4].iVal), PROGRAM_HEAD, NULL, NULL, NULL, NULL, NULL);
    }
#line 1573 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 75 "spl.y" /* yacc.c:1646  */
    {
    }
#line 1580 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 78 "spl.y" /* yacc.c:1646  */
    {
    }
#line 1587 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 82 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, ROUTINE, (yyvsp[-1].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
    }
#line 1595 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 87 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, SUB_ROUTINE, (yyvsp[-1].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
    }
#line 1603 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 92 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, ROUTINE_HEAD, (yyvsp[-4].tVal), (yyvsp[-3].tVal), (yyvsp[-2].tVal), (yyvsp[-1].tVal), (yyvsp[0].tVal));
    }
#line 1611 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 97 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, LABEL_PART, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 1619 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 101 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, LABEL_PART, NULL, NULL, NULL, NULL, NULL);
    }
#line 1627 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 106 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[0].iVal), LABEL_LIST, (yyvsp[-2].tVal), NULL, NULL, NULL, NULL);
    }
#line 1635 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 110 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[0].iVal), LABEL_LIST, NULL, NULL, NULL, NULL, NULL);
    }
#line 1643 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 115 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, CONST_PART, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 1651 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 119 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, CONST_PART, NULL, NULL, NULL, NULL, NULL);
    }
#line 1659 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 124 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[-3].iVal), CONST_EXPR_LIST, (yyvsp[-4].tVal), (yyvsp[-1].tVal), NULL, NULL, NULL);
    }
#line 1667 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 128 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[-3].iVal), CONST_EXPR_LIST, (yyvsp[-1].tVal), NULL, NULL, NULL, NULL);
    }
#line 1675 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 133 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[0].iVal), CONST_VALUE_INT, NULL, NULL, NULL, NULL, NULL);
    }
#line 1683 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 137 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[0].iVal), CONST_VALUE_REAL, NULL, NULL, NULL, NULL, NULL);
    }
#line 1691 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 141 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[0].iVal), CONST_VALUE_CHAR, NULL, NULL, NULL, NULL, NULL);
    }
#line 1699 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 145 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[0].iVal), CONST_VALUE_STR, NULL, NULL, NULL, NULL, NULL);
    }
#line 1707 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 149 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, CONST_VALUE, NULL, NULL, NULL, NULL, NULL);
    }
#line 1715 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 154 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(T_TRUE, CONST_VALUE, NULL, NULL, NULL, NULL, NULL);
    }
#line 1723 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 158 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(T_FALSE, CONST_VALUE, NULL, NULL, NULL, NULL, NULL);
    }
#line 1731 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 162 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(T_MAXINT, CONST_VALUE, NULL, NULL, NULL, NULL, NULL);
    }
#line 1739 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 167 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, TYPE_PART, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 1747 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 171 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, TYPE_PART, NULL, NULL, NULL, NULL, NULL);
    }
#line 1755 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 176 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, TYPE_DECL_LIST, (yyvsp[-1].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
    }
#line 1763 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 180 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, TYPE_DECL_LIST, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 1771 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 185 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[-3].iVal), TYPE_DEFINITION, (yyvsp[-1].tVal), NULL, NULL, NULL, NULL);
    }
#line 1779 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 190 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, TYPE_DECL, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 1787 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 194 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, TYPE_DECL, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 1795 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 198 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, TYPE_DECL, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 1803 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 203 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(T_CHAR, SYS_TYPE, NULL, NULL, NULL, NULL, NULL);
    }
#line 1811 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 207 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(T_INTEGER, SYS_TYPE, NULL, NULL, NULL, NULL, NULL);
    }
#line 1819 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 211 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(T_REAL, SYS_TYPE, NULL, NULL, NULL, NULL, NULL);
    }
#line 1827 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 215 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(T_BOOLEAN, SYS_TYPE, NULL, NULL, NULL, NULL, NULL);
    }
#line 1835 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 219 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(T_STR, SYS_TYPE, NULL, NULL, NULL, NULL, NULL);
    }
#line 1843 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 224 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, SIMPLE_TYPE_DECL, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 1851 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 228 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[0].iVal), SIMPLE_TYPE_DECL, NULL, NULL, NULL, NULL, NULL);
    }
#line 1859 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 232 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, SIMPLE_TYPE_DECL, (yyvsp[-1].tVal), NULL, NULL, NULL, NULL);
    }
#line 1867 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 236 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(T_DOTDOT, SIMPLE_TYPE_DECL, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
    }
#line 1875 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 240 "spl.y" /* yacc.c:1646  */
    {
        cst_tree tmp = create_node(T_MINUS, FACTOR_8, (yyvsp[-2].tVal), NULL, NULL, NULL, NULL);
        (yyval.tVal) = create_node(T_DOTDOT, SIMPLE_TYPE_DECL, tmp, (yyvsp[0].tVal), NULL, NULL, NULL);
    }
#line 1884 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 245 "spl.y" /* yacc.c:1646  */
    {
        cst_tree tmp1 = create_node(T_MINUS, FACTOR_8, (yyvsp[-3].tVal), NULL, NULL, NULL, NULL);
        cst_tree tmp2 = create_node(T_MINUS, FACTOR_8, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
        (yyval.tVal) = create_node(T_DOTDOT, SIMPLE_TYPE_DECL, tmp1, tmp2, NULL, NULL, NULL);
    }
#line 1894 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 251 "spl.y" /* yacc.c:1646  */
    {
        cst_tree tmp1 = create_node((yyvsp[-2].iVal), SIMPLE_TYPE_DECL, NULL, NULL, NULL, NULL, NULL);
        cst_tree tmp2 = create_node((yyvsp[0].iVal), SIMPLE_TYPE_DECL, NULL, NULL, NULL, NULL, NULL);
        (yyval.tVal) = create_node(T_DOTDOT, SIMPLE_TYPE_DECL, tmp1, tmp2, NULL, NULL, NULL);
    }
#line 1904 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 258 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, ARRAY_TYPE_DECL, (yyvsp[-3].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
    }
#line 1912 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 263 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, RECORD_TYPE_DECL, (yyvsp[-1].tVal), NULL, NULL, NULL, NULL);
    }
#line 1920 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 268 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, FIELD_DECL_LIST, (yyvsp[-1].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
    }
#line 1928 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 272 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, FIELD_DECL_LIST, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 1936 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 277 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, FIELD_DECL, (yyvsp[-3].tVal), (yyvsp[-1].tVal), NULL, NULL, NULL);
    }
#line 1944 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 282 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[0].iVal), NAME_LIST, (yyvsp[-2].tVal), NULL, NULL, NULL, NULL);
    }
#line 1952 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 286 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[0].iVal), NAME_LIST, NULL, NULL, NULL, NULL, NULL);
    }
#line 1960 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 291 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, VAR_PART, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 1968 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 295 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, VAR_PART, NULL, NULL, NULL, NULL, NULL);
    }
#line 1976 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 300 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, VAR_DECL_LIST, (yyvsp[-1].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
    }
#line 1984 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 304 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, VAR_DECL_LIST, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 1992 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 309 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, VAR_DECL, (yyvsp[-3].tVal), (yyvsp[-1].tVal), NULL, NULL, NULL);
    }
#line 2000 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 314 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, ROUTINE_PART, (yyvsp[-1].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
    }
#line 2008 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 318 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, ROUTINE_PART, (yyvsp[-1].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
    }
#line 2016 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 322 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, ROUTINE_PART, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 2024 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 326 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, ROUTINE_PART, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 2032 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 330 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, ROUTINE_PART, NULL, NULL, NULL, NULL, NULL);
    }
#line 2040 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 335 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, FUNCTION_DECL, (yyvsp[-3].tVal), (yyvsp[-1].tVal), NULL, NULL, NULL);
    }
#line 2048 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 340 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[-3].iVal), FUNCTION_HEAD, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
    }
#line 2056 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 345 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, PROCEDURE_DECL, (yyvsp[-3].tVal), (yyvsp[-1].tVal), NULL, NULL, NULL);
    }
#line 2064 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 350 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[-1].iVal), PROCEDURE_HEAD, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 2072 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 355 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, PARAMETERS, (yyvsp[-1].tVal), NULL, NULL, NULL, NULL);
    }
#line 2080 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 359 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, PARAMETERS, NULL, NULL, NULL, NULL, NULL);
    }
#line 2088 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 364 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, PARA_DECL_LIST, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
    }
#line 2096 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 368 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, PARA_DECL_LIST, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 2104 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 373 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, PARA_TYPE_LIST_1, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
    }
#line 2112 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 377 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, PARA_TYPE_LIST_2, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
    }
#line 2120 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 382 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, VAR_PARA_LIST, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 2128 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 387 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, VAL_PARA_LIST, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 2136 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 392 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, ROUTINE_BODY, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 2144 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 397 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, COMPOUND_STMT, (yyvsp[-1].tVal), NULL, NULL, NULL, NULL);
    }
#line 2152 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 402 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, STMT_LIST, (yyvsp[-2].tVal), (yyvsp[-1].tVal), NULL, NULL, NULL);
    }
#line 2160 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 406 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, STMT_LIST, NULL, NULL, NULL, NULL, NULL);
    }
#line 2168 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 411 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[-2].iVal), STMT, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 2176 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 415 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, STMT, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 2184 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 420 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, NON_LABEL_STMT, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 2192 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 424 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, NON_LABEL_STMT, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 2200 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 428 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, NON_LABEL_STMT, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 2208 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 432 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, NON_LABEL_STMT, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 2216 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 436 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, NON_LABEL_STMT, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 2224 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 440 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, NON_LABEL_STMT, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 2232 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 444 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, NON_LABEL_STMT, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 2240 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 448 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, NON_LABEL_STMT, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 2248 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 452 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, NON_LABEL_STMT, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 2256 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 457 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[-2].iVal), ASSIGN_STMT_1, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
    }
#line 2264 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 461 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[-5].iVal), ASSIGN_STMT_2, (yyvsp[-3].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
    }
#line 2272 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 465 "spl.y" /* yacc.c:1646  */
    {
        cst_tree tmp = create_node((yyvsp[-2].iVal), SIMPLE_TYPE_DECL, NULL, NULL, NULL, NULL, NULL);
        (yyval.tVal) = create_node((yyvsp[-4].iVal), ASSIGN_STMT_3, tmp, (yyvsp[0].tVal), NULL, NULL, NULL);
    }
#line 2281 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 471 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[0].iVal), PROC_STMT_1, NULL, NULL, NULL, NULL, NULL);
	}
#line 2289 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 475 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node((yyvsp[-3].iVal), PROC_STMT_2, (yyvsp[-1].tVal), NULL, NULL, NULL, NULL);
    }
#line 2297 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 479 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, PROC_STMT_3, (yyvsp[-3].tVal), (yyvsp[-1].tVal), NULL, NULL, NULL);
    }
#line 2305 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 483 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(NOTHING, PROC_STMT_4, (yyvsp[-3].tVal), (yyvsp[-1].tVal), NULL, NULL, NULL);
    }
#line 2313 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 488 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(T_WRITE, SYS_PROC, NULL, NULL, NULL, NULL, NULL);
    }
#line 2321 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 492 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(T_WRITELN, SYS_PROC, NULL, NULL, NULL, NULL, NULL);
    }
#line 2329 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 496 "spl.y" /* yacc.c:1646  */
    {
        (yyval.tVal) = create_node(T_READ, SYS_PROC, NULL, NULL, NULL, NULL, NULL);
    }
#line 2337 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 501 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, IF_STMT, (yyvsp[-3].tVal), (yyvsp[-1].tVal), (yyvsp[0].tVal), NULL, NULL);
	}
#line 2345 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 506 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, ELSE_CLAUSE, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
	}
#line 2353 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 510 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, ELSE_CLAUSE, NULL, NULL, NULL, NULL, NULL);
    }
#line 2361 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 515 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, REPEAT_STMT, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
	}
#line 2369 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 520 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, WHILE_STMT, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
	}
#line 2377 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 525 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node((yyvsp[-6].iVal), FOR_STMT, (yyvsp[-4].tVal), (yyvsp[-3].tVal), (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL);
	}
#line 2385 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 530 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_TO, DIRECTION, NULL, NULL, NULL, NULL, NULL);
	}
#line 2393 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 534 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_DOWNTO, DIRECTION, NULL, NULL, NULL, NULL, NULL);
	}
#line 2401 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 539 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, CASE_STMT, (yyvsp[-3].tVal), (yyvsp[-1].tVal), NULL, NULL, NULL);
	}
#line 2409 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 544 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, CASE_EXPR_LIST, (yyvsp[-1].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
	}
#line 2417 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 548 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, CASE_EXPR_LIST, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
	}
#line 2425 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 553 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, CASE_EXPR, (yyvsp[-3].tVal), (yyvsp[-1].tVal), NULL, NULL, NULL);
	}
#line 2433 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 557 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node((yyvsp[-3].iVal), CASE_EXPR, (yyvsp[-1].tVal), NULL, NULL, NULL, NULL);
	}
#line 2441 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 562 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node((yyvsp[0].iVal), GOTO_STMT, NULL, NULL, NULL, NULL, NULL);
	}
#line 2449 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 567 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, EXPRESSION_LIST, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
	}
#line 2457 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 571 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, EXPRESSION_LIST, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
	}
#line 2465 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 576 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_GE, EXPRESSION, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
	}
#line 2473 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 580 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_GT, EXPRESSION, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
	}
#line 2481 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 584 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_LE, EXPRESSION, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
	}
#line 2489 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 588 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_LT, EXPRESSION, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
	}
#line 2497 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 592 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_EQUAL, EXPRESSION, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
	}
#line 2505 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 596 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_NE, EXPRESSION, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
	}
#line 2513 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 600 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, EXPRESSION, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
	}
#line 2521 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 605 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_PLUS, PLUS_EXPR, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
	}
#line 2529 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 609 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_MINUS, MINUS_EXPR, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
	}
#line 2537 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 613 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_OR, OR_EXPR, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
	}
#line 2545 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 617 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, EXPR, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
	}
#line 2553 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 622 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_MUL, MUL_TERM, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
	}
#line 2561 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 626 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_DIV, DIV_TERM, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
	}
#line 2569 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 630 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_MOD, MOD_TERM, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
	}
#line 2577 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 634 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_AND, AND_TERM, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
	}
#line 2585 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 638 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, TERM, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
	}
#line 2593 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 643 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_ABS, SYS_FUNCT, NULL, NULL, NULL, NULL, NULL);
    }
#line 2601 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 647 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_CHR, SYS_FUNCT, NULL, NULL, NULL, NULL, NULL);
    }
#line 2609 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 651 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_ODD, SYS_FUNCT, NULL, NULL, NULL, NULL, NULL);
    }
#line 2617 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 655 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_ORD, SYS_FUNCT, NULL, NULL, NULL, NULL, NULL);
    }
#line 2625 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 659 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_PRED, SYS_FUNCT, NULL, NULL, NULL, NULL, NULL);
    }
#line 2633 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 663 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_SQR, SYS_FUNCT, NULL, NULL, NULL, NULL, NULL);
    }
#line 2641 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 667 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_SQRT, SYS_FUNCT, NULL, NULL, NULL, NULL, NULL);
    }
#line 2649 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 671 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_SUCC, SYS_FUNCT, NULL, NULL, NULL, NULL, NULL);
    }
#line 2657 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 677 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node((yyvsp[0].iVal), FACTOR_1, NULL, NULL, NULL, NULL, NULL);
	}
#line 2665 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 681 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node((yyvsp[-3].iVal), FACTOR_2, (yyvsp[-1].tVal), NULL, NULL, NULL, NULL);
	}
#line 2673 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 685 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, FACTOR_3, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
	}
#line 2681 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 689 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, FACTOR_4, (yyvsp[-3].tVal), (yyvsp[-1].tVal), NULL, NULL, NULL);
	}
#line 2689 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 693 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, FACTOR_5, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
	}
#line 2697 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 697 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, FACTOR_6, (yyvsp[-1].tVal), NULL, NULL, NULL, NULL);
	}
#line 2705 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 701 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_NOT, FACTOR_7, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
	}
#line 2713 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 705 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(T_MINUS, FACTOR_8, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
	}
#line 2721 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 709 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node((yyvsp[-3].iVal), FACTOR_9, (yyvsp[-1].tVal), NULL, NULL, NULL, NULL);
	}
#line 2729 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 713 "spl.y" /* yacc.c:1646  */
    {
        cst_tree tmp = create_node((yyvsp[0].iVal), SIMPLE_TYPE_DECL, NULL, NULL, NULL, NULL, NULL);
		(yyval.tVal) = create_node((yyvsp[-2].iVal), FACTOR_10, tmp, NULL, NULL, NULL, NULL);
	}
#line 2738 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 719 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, ARGS_LIST, (yyvsp[-2].tVal), (yyvsp[0].tVal), NULL, NULL, NULL);
	}
#line 2746 "spl.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 723 "spl.y" /* yacc.c:1646  */
    {
		(yyval.tVal) = create_node(NOTHING, ARGS_LIST, (yyvsp[0].tVal), NULL, NULL, NULL, NULL);
	}
#line 2754 "spl.tab.c" /* yacc.c:1646  */
    break;


#line 2758 "spl.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 727 "spl.y" /* yacc.c:1906  */


int main() {
    yyin = stdin;
    do {
        yyparse();
    } while (!feof(yyin));

    return 0;
}

