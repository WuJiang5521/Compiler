%{
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

%}

// start symbol
%start program

// token
%token T_LP T_RP T_LB T_RB T_DOT T_COMMA T_COLON T_PLUS T_MINUS T_MUL T_DIV T_GT T_LT T_EQUAL T_NE T_LE T_GE T_ASSIGN T_NOT 
        T_MOD T_DOTDOT T_SEMI T_AND T_ARRAY T_BEGIN T_CASE T_CONST T_DO T_DOWNTO T_ELSE T_END T_FOR T_FUNCTION T_GOTO 
        T_IF T_IN T_OF T_OR T_PACKED T_PROCEDURE T_PROGRAM T_RECORD T_REPEAT T_SET T_THEN T_TO T_TYPE T_UNTIL T_VAR T_WHILE T_WITH 
        T_ABS T_CHR T_ODD T_ORD T_PRED T_SQR T_SQRT T_SUCC T_WRITE T_WRITELN T_READ T_BOOLEAN T_CHAR T_INTEGER T_REAL T_STRING T_TRUE T_FALSE T_MAXINT

%union {
    int iVal;
    cst_tree tVal;
}

%token<iVal> S_ID S_INTEGER S_REAL S_CHAR S_STRING


%type<tVal> program program_head routine sub_routine routine_head label_part label_list const_part const_expr_list const_value type_part type_decl_list 
    type_definition type_decl simple_type_decl array_type_decl record_type_decl field_decl_list field_decl name_list var_part var_decl_list 
    var_decl routine_part function_decl function_head procedure_decl procedure_head parameters para_decl_list para_type_list var_para_list 
    val_para_list routine_body compound_stmt stmt_list stmt non_label_stmt assign_stmt proc_stmt if_stmt else_clause repeat_stmt while_stmt 
    for_stmt direction case_stmt case_expr_list case_expr goto_stmt expression_list expression expr term factor args_list sys_type sys_funct 
    sys_proc sys_con

%nonassoc "then"
%nonassoc T_ELSE
%nonassoc T_PROCEDURE
%nonassoc T_FUNCTION

%%
program : program_head routine T_DOT
    {
        cst_tree root = create_node(NOTHING, PROGRAM, $1, $2, NULL, NULL, NULL);
        ast_root = Translator::translate(root);
        ast::printTree("log", ast_root);
        $$ = root;
    };

program_head : T_PROGRAM S_ID T_SEMI
   {
        $$ = create_node($2, PROGRAM_HEAD, NULL, NULL, NULL, NULL, NULL);
    }
    | T_PROGRAM S_ID T_LP program_head_para T_RP T_SEMI
    {
        $$ = create_node($2, PROGRAM_HEAD, NULL, NULL, NULL, NULL, NULL);
    }
    ;

program_head_para : program_head_para T_COMMA S_ID
    {
    }
    | S_ID
    {
    };

routine : routine_head routine_body
    {
        $$ = create_node(NOTHING, ROUTINE, $1, $2, NULL, NULL, NULL);
    };

sub_routine : routine_head routine_body
    {
        $$ = create_node(NOTHING, ROUTINE, $1, $2, NULL, NULL, NULL);
    };

routine_head : label_part const_part type_part var_part routine_part
    {
        $$ = create_node(NOTHING, ROUTINE_HEAD, $1, $2, $3, $4, $5);
    };

label_part : label_list
    {
        $$ = create_node(NOTHING, LABEL_PART, $1, NULL, NULL, NULL, NULL);
    }
    | 
    {
        $$ = create_node(NOTHING, LABEL_PART, NULL, NULL, NULL, NULL, NULL);
    } /* empty */;

label_list : label_list T_COMMA S_INTEGER
    {
        $$ = create_node($3, LABEL_LIST, $1, NULL, NULL, NULL, NULL);
    }
    | S_INTEGER
    {
        $$ = create_node($1, LABEL_LIST, NULL, NULL, NULL, NULL, NULL);
    };

const_part : T_CONST const_expr_list
    {
        $$ = create_node(NOTHING, CONST_PART, $2, NULL, NULL, NULL, NULL);
    }
	|
    {
        $$ = create_node(NOTHING, CONST_PART, NULL, NULL, NULL, NULL, NULL);
    } /* empty */;

const_expr_list : const_expr_list S_ID T_EQUAL const_value T_SEMI
    {
        $$ = create_node($2, CONST_EXPR_LIST, $1, $4, NULL, NULL, NULL);
    }
	| S_ID T_EQUAL const_value T_SEMI
    {
        $$ = create_node($1, CONST_EXPR_LIST, $3, NULL, NULL, NULL, NULL);
    };

const_value : S_INTEGER
    {
        $$ = create_node($1, CONST_VALUE_INT, NULL, NULL, NULL, NULL, NULL);
    }
	| S_REAL
    {
        $$ = create_node($1, CONST_VALUE_REAL, NULL, NULL, NULL, NULL, NULL);
    }
	| S_CHAR
    {
        $$ = create_node($1, CONST_VALUE_CHAR, NULL, NULL, NULL, NULL, NULL);
    }
	| S_STRING
    {
        $$ = create_node($1, CONST_VALUE_STR, NULL, NULL, NULL, NULL, NULL);
    }
	| sys_con
    {
        $$ = create_node(NOTHING, CONST_VALUE, NULL, NULL, NULL, NULL, NULL);
    }

sys_con : T_TRUE
    {
        $$ = create_node(T_TRUE, CONST_VALUE, NULL, NULL, NULL, NULL, NULL);
    }
    | T_FALSE
    {
        $$ = create_node(T_FALSE, CONST_VALUE, NULL, NULL, NULL, NULL, NULL);
    }
    | T_MAXINT
    {
        $$ = create_node(T_MAXINT, CONST_VALUE, NULL, NULL, NULL, NULL, NULL);
    };

type_part : T_TYPE type_decl_list
    {
        $$ = create_node(NOTHING, TYPE_PART, $2, NULL, NULL, NULL, NULL);
    }
	|
    {
        $$ = create_node(NOTHING, TYPE_PART, NULL, NULL, NULL, NULL, NULL);
    } /* empty */;

type_decl_list : type_decl_list type_definition
    {
        $$ = create_node(NOTHING, TYPE_DECL_LIST, $1, $2, NULL, NULL, NULL);
    }
	| type_definition
    {
        $$ = create_node(NOTHING, TYPE_DECL_LIST, $1, NULL, NULL, NULL, NULL);
    };

type_definition : S_ID T_EQUAL type_decl T_SEMI
    {
        $$ = create_node($1, TYPE_DEFINITION, $3, NULL, NULL, NULL, NULL);
    };

type_decl : simple_type_decl
    {
        $$ = create_node(NOTHING, TYPE_DECL, $1, NULL, NULL, NULL, NULL);
    }
	| array_type_decl
    {
        $$ = create_node(NOTHING, TYPE_DECL, $1, NULL, NULL, NULL, NULL);
    }
	| record_type_decl
    {
        $$ = create_node(NOTHING, TYPE_DECL, $1, NULL, NULL, NULL, NULL);
    };

sys_type : T_CHAR
    {
        $$ = create_node(T_CHAR, SYS_TYPE, NULL, NULL, NULL, NULL, NULL);
    }
    | T_INTEGER
    {
        $$ = create_node(T_INTEGER, SYS_TYPE, NULL, NULL, NULL, NULL, NULL);
    }
    | T_REAL
    {
        $$ = create_node(T_REAL, SYS_TYPE, NULL, NULL, NULL, NULL, NULL);
    }
    | T_BOOLEAN
    {
        $$ = create_node(T_BOOLEAN, SYS_TYPE, NULL, NULL, NULL, NULL, NULL);
    }
    | T_STRING
    {
        $$ = create_node(T_STRING, SYS_TYPE, NULL, NULL, NULL, NULL, NULL);
    };

simple_type_decl : sys_type
    {
        $$ = create_node(NOTHING, SIMPLE_TYPE_DECL_1, $1, NULL, NULL, NULL, NULL);
    }
	| S_ID
    {
        $$ = create_node($1, SIMPLE_TYPE_DECL_2, NULL, NULL, NULL, NULL, NULL);
    }
	| T_LP name_list T_RP
    {
        $$ = create_node(NOTHING, SIMPLE_TYPE_DECL_3, $2, NULL, NULL, NULL, NULL);
    }
	| const_value T_DOTDOT const_value
    {
        $$ = create_node(T_DOTDOT, ARRAY_RANGE_1, $1, $3, NULL, NULL, NULL);
    }
	| T_MINUS const_value T_DOTDOT const_value
    {
        cst_tree tmp = create_node(T_MINUS, FACTOR_8, $2, NULL, NULL, NULL, NULL);
        $$ = create_node(T_DOTDOT, ARRAY_RANGE_2, $2, $4, NULL, NULL, NULL);
    }
	| T_MINUS const_value T_DOTDOT T_MINUS const_value
    {
        cst_tree tmp1 = create_node(T_MINUS, FACTOR_8, $2, NULL, NULL, NULL, NULL);
        cst_tree tmp2 = create_node(T_MINUS, FACTOR_8, $5, NULL, NULL, NULL, NULL);
        $$ = create_node(T_DOTDOT, ARRAY_RANGE_3, tmp1, tmp2, NULL, NULL, NULL);
    }
	| S_ID T_DOTDOT S_ID
    {
        cst_tree tmp1 = create_node($1, FACTOR_1, NULL, NULL, NULL, NULL, NULL);
        cst_tree tmp2 = create_node($3, FACTOR_1, NULL, NULL, NULL, NULL, NULL);
        $$ = create_node(T_DOTDOT, ARRAY_RANGE_4, tmp1, tmp2, NULL, NULL, NULL);
    };

array_type_decl : T_ARRAY T_LB simple_type_decl T_RB T_OF type_decl
    {
        $$ = create_node(NOTHING, ARRAY_TYPE_DECL, $3, $6, NULL, NULL, NULL);
    };

record_type_decl : T_RECORD field_decl_list T_END
    {
        $$ = create_node(NOTHING, RECORD_TYPE_DECL, $2, NULL, NULL, NULL, NULL);
    };

field_decl_list : field_decl_list field_decl
    {
        $$ = create_node(NOTHING, FIELD_DECL_LIST, $1, $2, NULL, NULL, NULL);
    }
	| field_decl
    {
        $$ = create_node(NOTHING, FIELD_DECL_LIST, $1, NULL, NULL, NULL, NULL);
    };

field_decl : name_list T_COLON type_decl T_SEMI
    {
        $$ = create_node(NOTHING, FIELD_DECL, $1, $3, NULL, NULL, NULL);
    };

name_list : name_list T_COMMA S_ID
    {
        $$ = create_node($3, NAME_LIST, $1, NULL, NULL, NULL, NULL);
    }
	| S_ID
    {
        $$ = create_node($1, NAME_LIST, NULL, NULL, NULL, NULL, NULL);
    };

var_part : T_VAR var_decl_list
    {
        $$ = create_node(NOTHING, VAR_PART, $2, NULL, NULL, NULL, NULL);
    }
	|
    {
        $$ = create_node(NOTHING, VAR_PART, NULL, NULL, NULL, NULL, NULL);
    } /* empty */;

var_decl_list : var_decl_list var_decl
    {
        $$ = create_node(NOTHING, VAR_DECL_LIST, $1, $2, NULL, NULL, NULL);
    }
	| var_decl
    {
        $$ = create_node(NOTHING, VAR_DECL_LIST, $1, NULL, NULL, NULL, NULL);
    };

var_decl : name_list T_COLON type_decl T_SEMI
    {
        $$ = create_node(NOTHING, VAR_DECL, $1, $3, NULL, NULL, NULL);
    };

routine_part: routine_part function_decl
    {
        $$ = create_node(NOTHING, ROUTINE_PART, $1, $2, NULL, NULL, NULL);
    }
	| routine_part procedure_decl
    {
        $$ = create_node(NOTHING, ROUTINE_PART, $1, $2, NULL, NULL, NULL);
    }
	| function_decl
    {
        $$ = create_node(NOTHING, ROUTINE_PART, $1, NULL, NULL, NULL, NULL);
    }
	| procedure_decl
    {
        $$ = create_node(NOTHING, ROUTINE_PART, $1, NULL, NULL, NULL, NULL);
    }
	|   %prec "then"
    {
        $$ = create_node(NOTHING, ROUTINE_PART, NULL, NULL, NULL, NULL, NULL);
    } /* empty */;

function_decl : function_head T_SEMI sub_routine T_SEMI
    {
        $$ = create_node(NOTHING, FUNCTION_DECL, $1, $3, NULL, NULL, NULL);
    };

function_head : T_FUNCTION S_ID parameters T_COLON simple_type_decl
    {
        $$ = create_node($2, FUNCTION_HEAD, $3, $5, NULL, NULL, NULL);
    };

procedure_decl : procedure_head T_SEMI sub_routine T_SEMI
    {
        $$ = create_node(NOTHING, PROCEDURE_DECL, $1, $3, NULL, NULL, NULL);
    };

procedure_head : T_PROCEDURE S_ID parameters
    {
        $$ = create_node($2, PROCEDURE_HEAD, $3, NULL, NULL, NULL, NULL);
    };

parameters : T_LP para_decl_list T_RP
    {
        $$ = create_node(NOTHING, PARAMETERS, $2, NULL, NULL, NULL, NULL);
    }
	|
    {
        $$ = create_node(NOTHING, PARAMETERS, NULL, NULL, NULL, NULL, NULL);
    } /* empty */;

para_decl_list : para_decl_list T_SEMI para_type_list
    {
        $$ = create_node(NOTHING, PARA_DECL_LIST, $1, $3, NULL, NULL, NULL);
    }
	| para_type_list
    {
        $$ = create_node(NOTHING, PARA_DECL_LIST, $1, NULL, NULL, NULL, NULL);
    };

para_type_list : var_para_list T_COLON simple_type_decl
    {
        $$ = create_node(NOTHING, PARA_TYPE_LIST_1, $1, $3, NULL, NULL, NULL);
    }
	| val_para_list T_COLON simple_type_decl
    {
        $$ = create_node(NOTHING, PARA_TYPE_LIST_2, $1, $3, NULL, NULL, NULL);
    };

var_para_list : T_VAR name_list
    {
        $$ = create_node(NOTHING, VAR_PARA_LIST, $2, NULL, NULL, NULL, NULL);
    };

val_para_list : name_list
    {
        $$ = create_node(NOTHING, VAL_PARA_LIST, $1, NULL, NULL, NULL, NULL);
    };

routine_body : compound_stmt
    {
        $$ = create_node(NOTHING, ROUTINE_BODY, $1, NULL, NULL, NULL, NULL);
    };

compound_stmt : T_BEGIN stmt_list T_END
    {
        $$ = create_node(NOTHING, COMPOUND_STMT, $2, NULL, NULL, NULL, NULL);
    };

stmt_list : stmt_list stmt T_SEMI
    {
        $$ = create_node(NOTHING, STMT_LIST, $1, $2, NULL, NULL, NULL);
    }
	|
    {
        $$ = create_node(NOTHING, STMT_LIST, NULL, NULL, NULL, NULL, NULL);
    } /* empty */;

stmt : S_INTEGER T_COLON non_label_stmt
    {
        $$ = create_node($1, STMT, $3, NULL, NULL, NULL, NULL);
    }
	| non_label_stmt
    {
        $$ = create_node(NOTHING, STMT, $1, NULL, NULL, NULL, NULL);
    };

non_label_stmt : assign_stmt
    {
        $$ = create_node(NOTHING, NON_LABEL_STMT, $1, NULL, NULL, NULL, NULL);
    }
	| proc_stmt
    {
        $$ = create_node(NOTHING, NON_LABEL_STMT, $1, NULL, NULL, NULL, NULL);
    }
	| compound_stmt
    {
        $$ = create_node(NOTHING, NON_LABEL_STMT, $1, NULL, NULL, NULL, NULL);
    }
	| if_stmt
    {
        $$ = create_node(NOTHING, NON_LABEL_STMT, $1, NULL, NULL, NULL, NULL);
    }
	| repeat_stmt
    {
        $$ = create_node(NOTHING, NON_LABEL_STMT, $1, NULL, NULL, NULL, NULL);
    }
	| while_stmt
    {
        $$ = create_node(NOTHING, NON_LABEL_STMT, $1, NULL, NULL, NULL, NULL);
    }
	| for_stmt
    {
        $$ = create_node(NOTHING, NON_LABEL_STMT, $1, NULL, NULL, NULL, NULL);
    }
	| case_stmt
    {
        $$ = create_node(NOTHING, NON_LABEL_STMT, $1, NULL, NULL, NULL, NULL);
    }
	| goto_stmt
    {
        $$ = create_node(NOTHING, NON_LABEL_STMT, $1, NULL, NULL, NULL, NULL);
    };

assign_stmt : S_ID T_ASSIGN expression      // id = 3
    {
        $$ = create_node($1, ASSIGN_STMT_1, $3, NULL, NULL, NULL, NULL);
    }
	| S_ID T_LB expression T_RB T_ASSIGN expression     // id[3] = 4
    {
        $$ = create_node($1, ASSIGN_STMT_2, $3, $6, NULL, NULL, NULL);
    }
	| S_ID T_DOT S_ID T_ASSIGN expression       // id.key = 10
    {
        cst_tree tmp = create_node($3, FACTOR_1, NULL, NULL, NULL, NULL, NULL);
        $$ = create_node($1, ASSIGN_STMT_3, tmp, $5, NULL, NULL, NULL);
    };

proc_stmt : S_ID
	{
        $$ = create_node($1, PROC_STMT_1, NULL, NULL, NULL, NULL, NULL);
	}
	| S_ID T_LP args_list T_RP
    {
        $$ = create_node($1, PROC_STMT_2, $3, NULL, NULL, NULL, NULL);
    }
	| sys_proc T_LP expression_list T_RP
    {
        $$ = create_node(NOTHING, PROC_STMT_3, $1, $3, NULL, NULL, NULL);
    }
	| sys_proc T_LP factor T_RP
    {
        $$ = create_node(NOTHING, PROC_STMT_4, $1, $3, NULL, NULL, NULL);
    };

sys_proc : T_WRITE
    {
        $$ = create_node(T_WRITE, SYS_PROC, NULL, NULL, NULL, NULL, NULL);
    }
    | T_WRITELN
    {
        $$ = create_node(T_WRITELN, SYS_PROC, NULL, NULL, NULL, NULL, NULL);
    }
    | T_READ
    {
        $$ = create_node(T_READ, SYS_PROC, NULL, NULL, NULL, NULL, NULL);
    };

if_stmt : T_IF expression T_THEN stmt else_clause
	{
		$$ = create_node(NOTHING, IF_STMT, $2, $4, $5, NULL, NULL);
	};

else_clause : T_ELSE stmt
	{
		$$ = create_node(NOTHING, ELSE_CLAUSE, $2, NULL, NULL, NULL, NULL);
	}
	|   %prec "then"
    {
		$$ = create_node(NOTHING, ELSE_CLAUSE, NULL, NULL, NULL, NULL, NULL);
    } /* empty */;

repeat_stmt : T_REPEAT stmt_list T_UNTIL expression
	{
		$$ = create_node(NOTHING, REPEAT_STMT, $2, $4, NULL, NULL, NULL);
	};

while_stmt : T_WHILE expression T_DO stmt
	{
		$$ = create_node(NOTHING, WHILE_STMT, $2, $4, NULL, NULL, NULL);
	};

for_stmt : T_FOR S_ID T_ASSIGN expression direction expression T_DO stmt
	{
		$$ = create_node($2, FOR_STMT, $4, $5, $6, $8, NULL);
	};

direction : T_TO
	{
		$$ = create_node(T_TO, DIRECTION, NULL, NULL, NULL, NULL, NULL);
	}
	| T_DOWNTO
	{
		$$ = create_node(T_DOWNTO, DIRECTION, NULL, NULL, NULL, NULL, NULL);
	};

case_stmt : T_CASE expression T_OF case_expr_list T_END
	{
		$$ = create_node(NOTHING, CASE_STMT, $2, $4, NULL, NULL, NULL);
	};

case_expr_list : case_expr_list case_expr
	{
		$$ = create_node(NOTHING, CASE_EXPR_LIST, $1, $2, NULL, NULL, NULL);
	}
	| case_expr
	{
		$$ = create_node(NOTHING, CASE_EXPR_LIST, $1, NULL, NULL, NULL, NULL);
	};

case_expr : const_value T_COLON stmt T_SEMI
	{
		$$ = create_node(NOTHING, CASE_EXPR, $1, $3, NULL, NULL, NULL);
	}
	| S_ID T_COLON stmt T_SEMI
	{
		$$ = create_node($1, CASE_EXPR, $3, NULL, NULL, NULL, NULL);
	};

goto_stmt : T_GOTO S_INTEGER
	{
		$$ = create_node($2, GOTO_STMT, NULL, NULL, NULL, NULL, NULL);
	};

expression_list : expression_list T_COMMA expression
	{
		$$ = create_node(NOTHING, EXPRESSION_LIST, $1, $3, NULL, NULL, NULL);
	}
	| expression
	{
		$$ = create_node(NOTHING, EXPRESSION_LIST, $1, NULL, NULL, NULL, NULL);
	};

expression : expression T_GE expr
	{
		$$ = create_node(T_GE, EXPRESSION, $1, $3, NULL, NULL, NULL);
	}
	| expression T_GT expr
	{
		$$ = create_node(T_GT, EXPRESSION, $1, $3, NULL, NULL, NULL);
	}
	| expression T_LE expr
	{
		$$ = create_node(T_LE, EXPRESSION, $1, $3, NULL, NULL, NULL);
	}
	| expression T_LT expr
	{
		$$ = create_node(T_LT, EXPRESSION, $1, $3, NULL, NULL, NULL);
	}
	| expression T_EQUAL expr
	{
		$$ = create_node(T_EQUAL, EXPRESSION, $1, $3, NULL, NULL, NULL);
	}
	| expression T_NE expr
	{
		$$ = create_node(T_NE, EXPRESSION, $1, $3, NULL, NULL, NULL);
	}
	| expr
	{
		$$ = create_node(NOTHING, EXPRESSION, $1, NULL, NULL, NULL, NULL);
	};

expr : expr T_PLUS term
	{
		$$ = create_node(T_PLUS, PLUS_EXPR, $1, $3, NULL, NULL, NULL);
	}
	| expr T_MINUS term
	{
		$$ = create_node(T_MINUS, MINUS_EXPR, $1, $3, NULL, NULL, NULL);
	}
	| expr T_OR term
	{
		$$ = create_node(T_OR, OR_EXPR, $1, $3, NULL, NULL, NULL);
	}
	| term
	{
		$$ = create_node(NOTHING, EXPR, $1, NULL, NULL, NULL, NULL);
	};

term : term T_MUL factor
	{
		$$ = create_node(T_MUL, MUL_TERM, $1, $3, NULL, NULL, NULL);
	}
	| term T_DIV factor
	{
		$$ = create_node(T_DIV, DIV_TERM, $1, $3, NULL, NULL, NULL);
	}
	| term T_MOD factor
	{
		$$ = create_node(T_MOD, MOD_TERM, $1, $3, NULL, NULL, NULL);
	}
	| term T_AND factor
	{
		$$ = create_node(T_AND, AND_TERM, $1, $3, NULL, NULL, NULL);
	}
	| factor
	{
		$$ = create_node(NOTHING, TERM, $1, NULL, NULL, NULL, NULL);
	};

sys_funct : T_ABS
    {
		$$ = create_node(T_ABS, SYS_FUNCT, NULL, NULL, NULL, NULL, NULL);
    }
    | T_CHR
    {
		$$ = create_node(T_CHR, SYS_FUNCT, NULL, NULL, NULL, NULL, NULL);
    }
    | T_ODD
    {
		$$ = create_node(T_ODD, SYS_FUNCT, NULL, NULL, NULL, NULL, NULL);
    }
    | T_ORD
    {
		$$ = create_node(T_ORD, SYS_FUNCT, NULL, NULL, NULL, NULL, NULL);
    }
    | T_PRED
    {
		$$ = create_node(T_PRED, SYS_FUNCT, NULL, NULL, NULL, NULL, NULL);
    }
    | T_SQR
    {
		$$ = create_node(T_SQR, SYS_FUNCT, NULL, NULL, NULL, NULL, NULL);
    }
    | T_SQRT
    {
		$$ = create_node(T_SQRT, SYS_FUNCT, NULL, NULL, NULL, NULL, NULL);
    }
    | T_SUCC
    {
		$$ = create_node(T_SUCC, SYS_FUNCT, NULL, NULL, NULL, NULL, NULL);
    };


factor : S_ID
	{
		$$ = create_node($1, FACTOR_1, NULL, NULL, NULL, NULL, NULL);
	}
	| S_ID T_LP args_list T_RP
	{
		$$ = create_node($1, FACTOR_2, $3, NULL, NULL, NULL, NULL);
	}
	| sys_funct
	{
		$$ = create_node(NOTHING, FACTOR_3, $1, NULL, NULL, NULL, NULL);
	}
	| sys_funct T_LP args_list T_RP
	{
		$$ = create_node(NOTHING, FACTOR_4, $1, $3, NULL, NULL, NULL);
	}
	| const_value
	{
		$$ = create_node(NOTHING, FACTOR_5, $1, NULL, NULL, NULL, NULL);
	}
	| T_LP expression T_RP
	{
		$$ = create_node(NOTHING, FACTOR_6, $2, NULL, NULL, NULL, NULL);
	}
	| T_NOT factor
	{
		$$ = create_node(T_NOT, FACTOR_7, $2, NULL, NULL, NULL, NULL);
	}
	| T_MINUS factor
	{
		$$ = create_node(T_MINUS, FACTOR_8, $2, NULL, NULL, NULL, NULL);
	}
	| S_ID T_LB expression T_RB
	{
		$$ = create_node($1, FACTOR_9, $3, NULL, NULL, NULL, NULL);
	}
	| S_ID T_DOT S_ID
	{
        cst_tree tmp = create_node($3, FACTOR_1, NULL, NULL, NULL, NULL, NULL);
		$$ = create_node($1, FACTOR_10, tmp, NULL, NULL, NULL, NULL);
	};

args_list : args_list T_COMMA expression
	{
		$$ = create_node(NOTHING, ARGS_LIST, $1, $3, NULL, NULL, NULL);
	}
	| expression
	{
		$$ = create_node(NOTHING, ARGS_LIST, $1, NULL, NULL, NULL, NULL);
	};

%%

int doyyparse() {
    yyin = stdin;
    do {
        yyparse();
    } while (!feof(yyin));

    return 0;
}

