%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOTHING -1

enum ParseTreeNodeType {
  PROGRAM, PROGRAM_HEAD, ROUTINE, SUB_ROUTINE, ROUTINE_HEAD, LABEL_PART, CONST_PART, CONST_EXPR_LIST, CONST_VALUE, TYPE_PART, 
  TYPE_DECL_LIST, TYPE_DEFINITION, TYPE_DECL, SIMPLE_TYPE_DECL, ARRAY_TYPE_DECL, RECORD_TYPE_DECL, FIELD_DECL_LIST, FIELD_DECL, 
  NAME_LIST, VAR_PART, VAR_DECL_LIST, VAR_DECL, ROUTINE_PART, FUNCTION_DECL, FUNCTION_HEAD, PROCEDURE_DECL, PROCEDURE_HEAD, PARAMETERS, 
  PARA_DECL_LIST, PARA_TYPE_LIST, VAR_PARA_LIST, VAL_PARA_LIST, ROUTINE_BODY, COMPOUND_STMT, STMT_LIST, STMT, NON_LABEL_STMT, 
  ASSIGN_STMT, PROC_STMT, IF_STMT, ELSE_CLAUSE, REPEAT_STMT, WHILE_STMT, FOR_STMT, DIRECTION, CASE_STMT, CASE_EXPR_LIST, CASE_EXPR, 
  GOTO_STMT, EXPRESSION_LIST, EXPRESSION, EXPR, TERM, FACTOR, ARGS_LIST, SYS_TYPE, SYS_FUNCT, SYS_PROC, SYS_CON
}

typedef struct treeNode node;
typedef node* tree;
struct treeNode {
  int item;
  int node_id;
  tree first;
  tree second;
  tree third;
  tree fourth;
  tree fifth;
}

tree create_node(int ival int case_id, tree t1, tree t2, tree t3, tree t4, tree t5);

%}

// start symbol
%start program

// token
%token T_LP T_RP T_LB T_RB T_DOT T_COMMA T_COLON T_PLUS T_MINUS T_MUL T_DIV T_GT T_LT T_EQUAL T_NE T_LE T_GE T_ASSIGN T_NOT 
        T_MOD T_DOTDOT T_SEMI T_AND T_ARRAY T_BEGIN T_CASE T_CONST T_DO T_DOWNTO T_ELSE T_END T_FOR T_FUNCTION T_GOTO 
        T_IF T_IN T_OF T_OR T_PACKED T_PROCEDURE T_PROGRAM T_RECORD T_REPEAT T_SET T_THEN T_TO T_TYPE T_UNTIL T_VAR T_WHILE T_WITH 
        T_ABS T_CHR T_ODD T_ORD T_PRED T_SQR T_SQRT T_SUCC T_WRITE T_WRITELN T_READ T_BOOLEAN T_CHAR T_INTEGER T_REAL T_TRUE T_FALSE T_MAXINT

%union {
    int iVal;
    tree tVal;
}

%token<iVal> S_ID S_CHAR S_INTEGER S_REAL S_STRING

%type<tVal> program program_head routine sub_routine routine_head label_part const_part const_expr_list const_value type_part type_decl_list 
    type_definition type_decl simple_type_decl array_type_decl record_type_decl field_decl_list field_decl name_list var_part var_decl_list 
    var_decl routine_part function_decl function_head procedure_decl procedure_head parameters para_decl_list para_type_list var_para_list 
    val_para_list routine_body compound_stmt stmt_list stmt non_label_stmt assign_stmt proc_stmt if_stmt else_clause repeat_stmt while_stmt 
    for_stmt direction case_stmt case_expr_list case_expr goto_stmt expression_list expression expr term factor args_list sys_type sys_funct 
    sys_proc sys_con

%%
program : program_head routine T_DOT
    {
        $$ = create_node(NOTHING, PROGRAM, $1, $2, NULL, NULL, NULL);
    };

program_head : T_PROGRAM S_ID T_SEMI
    {
        $$ = create_node($2, PROCEDURE_HEAD, NULL, NULL, NULL, NULL, NULL);
    };

routine : routine_head routine_body
    {
        $$ = create_node(NOTHING, ROUTINE, $1, $2, NULL, NULL, NULL);
    };

sub_routine : routine_head routine_body
    {
        $$ = create_node(NOTHING, SUB_ROUTINE, $1, $2, NULL, NULL, NULL);
    };

routine_head : label_part const_part type_part var_part routine_part
    {
        $$ = create_node(NOTHING, ROUTINE_HEAD, $1, $2, $3, $4, $5);
    };

label_part : S_INTEGER
    {
        $$ = create_node(NOTHING, LABEL_PART, $1, NULL, NULL, NULL, NULL);
    }
    | /* empty */;

const_part : T_CONST const_expr_list
    {
        $$ = create_node(NOTHING, CONST_PART, $2, NULL, NULL, NULL, NULL);
    }
	| /* empty */;

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
        $$ = create_node(NOTHING, CONST_VALUE, $1, NULL, NULL, NULL, NULL);
    }
	| S_REAL
    {
        $$ = create_node(NOTHING, CONST_VALUE, $1, NULL, NULL, NULL, NULL);
    }
	| S_CHAR
    {
        $$ = create_node(NOTHING, CONST_VALUE, $1, NULL, NULL, NULL, NULL);
    }
	| S_STRING
    {
        $$ = create_node(NOTHING, CONST_VALUE, $1, NULL, NULL, NULL, NULL);
    }
	| sys_con
    {
        $$ = create_node(NOTHING, CONST_VALUE, $1, NULL, NULL, NULL, NULL);
    }

sys_con : T_TRUE
    {
        $$ = create_node(NOTHING, CONST_VALUE, T_TRUE, NULL, NULL, NULL, NULL);
    }
    | T_FALSE
    {
        $$ = create_node(NOTHING, CONST_VALUE, T_FALSE, NULL, NULL, NULL, NULL);
    }
    | T_MAXINT
    {
        $$ = create_node(NOTHING, CONST_VALUE, T_MAXINT, NULL, NULL, NULL, NULL);
    };

type_part : T_TYPE type_decl_list
    {
        $$ = create_node(NOTHING, TYPE_PART, $2, NULL, NULL, NULL, NULL);
    }
	| /* empty */;

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
    };

simple_type_decl : sys_type
    {
        $$ = create_node(NOTHING, SIMPLE_TYPE_DECL, $1, NULL, NULL, NULL, NULL);
    }
	| S_ID
    {
        $$ = create_node(NOTHING, SIMPLE_TYPE_DECL, $1, NULL, NULL, NULL, NULL);
    }
	| T_LP name_list T_RP
    {
        $$ = create_node(NOTHING, SIMPLE_TYPE_DECL, $2, NULL, NULL, NULL, NULL);
    }
	| const_value T_DOTDOT const_value
    {
        $$ = create_node(NOTHING, SIMPLE_TYPE_DECL, $1, T_DOTDOT, $3, NULL, NULL);
    }
	| T_MINUS const_value T_DOTDOT const_value
    {
        $$ = create_node(NOTHING, SIMPLE_TYPE_DECL, T_MINUS, $2, T_DOTDOT, $4, NULL);
    }
	| T_MINUS const_value T_DOTDOT T_MINUS const_value
    {
        $$ = create_node(NOTHING, SIMPLE_TYPE_DECL, T_MINUS, $2, T_DOTDOT, T_MINUS, $5);
    }
	| S_ID T_DOTDOT S_ID
    {
        $$ = create_node(NOTHING, SIMPLE_TYPE_DECL, $1, T_DOTDOT, $3, NULL, NULL);
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
        $$ = create_node(NOTHING, NAME_LIST, $1, $3, NULL, NULL, NULL);
    }
	| S_ID
    {
        $$ = create_node(NOTHING, NAME_LIST, $1, NULL, NULL, NULL, NULL);
    };

var_part : T_VAR var_decl_list
    {
        $$ = create_node(NOTHING, VAR_PART, $2, NULL, NULL, NULL, NULL);
    }
	| /* empty */;

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
	| /* empty */;

function_decl : function_head T_SEMI sub_routine T_SEMI
    {
        $$ = create_node(NOTHING, FUNCTION_DECL, $1, $3, NULL, NULL, NULL);
    };

function_head : T_FUNCTION S_ID parameters T_COLON simple_type_decl
    {
        $$ = create_node(NOTHING, FUNCTION_HEAD, $2, $3, $5, NULL, NULL);
    };

procedure_decl : procedure_head T_SEMI sub_routine T_SEMI
    {
        $$ = create_node(NOTHING, PROCEDURE_DECL, $1, $3, NULL, NULL, NULL);
    };

procedure_head : T_PROCEDURE S_ID parameters
    {
        $$ = create_node(NOTHING, PROCEDURE_HEAD, $2, $3, NULL, NULL, NULL);
    };

parameters : T_LP para_decl_list T_RP
    {
        $$ = create_node(NOTHING, PARAMETERS, $2, NULL, NULL, NULL, NULL);
    }
	| /* empty */;

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
        $$ = create_node(NOTHING, PARA_TYPE_LIST, $1, $3, NULL, NULL, NULL);
    }
	| val_para_list T_COLON simple_type_decl
    {
        $$ = create_node(NOTHING, PARA_TYPE_LIST, $1, $3, NULL, NULL, NULL);
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
	| /* empty */;

stmt : S_INTEGER T_COLON non_label_stmt
    {
        $$ = create_node(NOTHING, STMT, $1, $3, NULL, NULL, NULL);
    }
	| non_label_stmt
    {
        $$ = create_node(NOTHING, STMT, $1, NULL, NULL, NULL, NULL);
    };

non_label_stmt : assign_stmt
    {
    }
	| proc_stmt
    {
    }
	| compound_stmt
    {
    }
	| if_stmt
    {
    }
	| repeat_stmt
    {
    }
	| while_stmt
    {
    }
	| for_stmt
    {
    }
	| case_stmt
    {
    }
	| goto_stmt
    {
    };

assign_stmt : S_ID T_ASSIGN expression
    {
    }
	| S_ID T_LB expression T_RB T_ASSIGN expression
    {
    }
	| S_ID T_DOT S_ID T_ASSIGN expression
    {
    };

proc_stmt : S_ID
	{

	}
	| S_ID T_LP args_list T_RP
    {
    }
	| sys_proc T_LP expression_list T_RP
    {
    }
	| sys_proc T_LP factor T_RP
    {
    };

sys_proc : T_WRITE
    {
    }
    | T_WRITELN
    {
    }
    | T_READ
    {
    };

if_stmt : T_IF expression T_THEN stmt else_clause
	{
		$$ = create_node(NOTHING, IF_STMT, $2, $4, $5, NULL, NULL);
	};

else_clause : T_ELSE stmt
	{
		$$ = create_node(NOTHING, ELSE_CLAUSE, $2, NULL, NULL, NULL, NULL);
	}
	| /* empty */;

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
		$$ = create_node(NOTHING, DIRECTION, T_TO, NULL, NULL, NULL, NULL);
	}
	| T_DOWNTO
	{
		$$ = create_node(NOTHING, DIRECTION, T_DOWNTO, NULL, NULL, NULL, NULL);
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
		$$ = create_node(NOTHING, GOTO_STMT, $2, NULL, NULL, NULL, NULL);
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
		$$ = create_node(NOTHING, EXPRESSION, $1, T_GE, $3, NULL, NULL);
	}
	| expression T_GT expr
	{
		$$ = create_node(NOTHING, EXPRESSION, $1, T_GT, $3, NULL, NULL);
	}
	| expression T_LE expr
	{
		$$ = create_node(NOTHING, EXPRESSION, $1, T_LE, $3, NULL, NULL);
	}
	| expression T_LT expr
	{
		$$ = create_node(NOTHING, EXPRESSION, $1, T_LT, $3, NULL, NULL);
	}
	| expression T_EQUAL expr
	{
		$$ = create_node(NOTHING, EXPRESSION, $1, T_EQUAL, $3, NULL, NULL);
	}
	| expression T_NE expr
	{
		$$ = create_node(NOTHING, EXPRESSION, $1, T_NE, $3, NULL, NULL);
	}
	| expr
	{
		$$ = create_node(NOTHING, EXPRESSION, $1, NULL, NULL, NULL, NULL);
	};

expr : expr T_PLUS term
	{
		$$ = create_node(NOTHING, EXPR, $1, T_PLUS, $3, NULL, NULL);
	}
	| expr T_MINUS term
	{
		$$ = create_node(NOTHING, EXPR, $1, T_MINUS, $3, NULL, NULL);
	}
	| expr T_OR term
	{
		$$ = create_node(NOTHING, EXPR, $1, T_OR, $3, NULL, NULL);
	}
	| term
	{
		$$ = create_node(NOTHING, EXPR, $1, NULL, NULL, NULL, NULL);
	};

term : term T_MUL factor
	{
		$$ = create_node(NOTHING, TERM, $1, T_MUL, $3, NULL, NULL);
	}
	| term T_DIV factor
	{
		$$ = create_node(NOTHING, TERM, $1, T_DIV, $3, NULL, NULL);
	}
	| term T_MOD factor
	{
		$$ = create_node(NOTHING, TERM, $1, T_MOD, $3, NULL, NULL);
	}
	| term T_AND factor
	{
		$$ = create_node(NOTHING, TERM, $1, T_AND, $3, NULL, NULL);
	}
	| factor
	{
		$$ = create_node(NOTHING, TERM, $1, NULL, NULL, NULL, NULL);
	};

sys_funct : T_ABS
    {
		$$ = create_node(NOTHING, SYS_FUNCT, T_ABS, NULL, NULL, NULL, NULL);
    }
    | T_CHR
    {
		$$ = create_node(NOTHING, SYS_FUNCT, T_CHR, NULL, NULL, NULL, NULL);
    }
    | T_ODD
    {
		$$ = create_node(NOTHING, SYS_FUNCT, T_ODD, NULL, NULL, NULL, NULL);
    }
    | T_ORD
    {
		$$ = create_node(NOTHING, SYS_FUNCT, T_ORD, NULL, NULL, NULL, NULL);
    }
    | T_PRED
    {
		$$ = create_node(NOTHING, SYS_FUNCT, T_PRED, NULL, NULL, NULL, NULL);
    }
    | T_SQR
    {
		$$ = create_node(NOTHING, SYS_FUNCT, T_SQR, NULL, NULL, NULL, NULL);
    }
    | T_SQRT
    {
		$$ = create_node(NOTHING, SYS_FUNCT, T_SQRT, NULL, NULL, NULL, NULL);
    }
    | T_SUCC
    {
		$$ = create_node(NOTHING, SYS_FUNCT, T_SUCC, NULL, NULL, NULL, NULL);
    };


factor : S_ID
	{
		$$ = create_node(NOTHING, FACTOR, $1, NULL, NULL, NULL, NULL);
	}
	| S_ID T_LP args_list T_RP
	{
		$$ = create_node(NOTHING, FACTOR, $1, $3, NULL, NULL, NULL);
	}
	| sys_funct
	{
		$$ = create_node(NOTHING, FACTOR, $1, NULL, NULL, NULL, NULL);
	}
	| sys_funct T_LP args_list T_RP
	{
		$$ = create_node(NOTHING, FACTOR, $1, $3, NULL, NULL, NULL);
	}
	| const_value
	{
		$$ = create_node(NOTHING, FACTOR, $1, NULL, NULL, NULL, NULL);
	}
	| T_LP expression T_RP
	{
		$$ = create_node(NOTHING, FACTOR, $2, NULL, NULL, NULL, NULL);
	}
	| T_NOT factor
	{
		$$ = create_node(NOTHING, FACTOR, T_NOT, $2, NULL, NULL, NULL);
	}
	| T_MINUS factor
	{
		$$ = create_node(NOTHING, FACTOR, T_MINUS, $2, NULL, NULL, NULL);
	}
	| S_ID T_LB expression T_RB
	{
		$$ = create_node(NOTHING, FACTOR, $1, $3, NULL, NULL, NULL);
	}
	| S_ID T_DOT S_ID
	{
		$$ = create_node(NOTHING, FACTOR, $1, T_DOT, $3, NULL, NULL);
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

tree create_node(int ival int case_id, tree t1, tree t2, tree t3, tree t4, tree t5) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->item = ival;
    new_node->node_id = case_id;
    new_node->first = t1;
    new_node->second = t2;
    new_node->third = t3;
    new_node->fourth = t4;
    new_node->fifth = t5;
    return new_node;
}
