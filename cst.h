/*
 * cst.h
 * Copyright (C) 2018 weihao <blackhatdwh@gmail.com>
 *
 * Distributed under terms of the MIT license.
 * definition of contrete syntax tree
 */

#ifndef CST_H
#define CST_H

#define NOTHING -1
enum ParseTreeNodeType {
  PROGRAM, PROGRAM_HEAD, ROUTINE, SUB_ROUTINE, ROUTINE_HEAD, LABEL_PART, LABEL_LIST, CONST_PART, CONST_EXPR_LIST, CONST_VALUE, CONST_VALUE_INT, 
  CONST_VALUE_REAL, CONST_VALUE_CHAR, CONST_VALUE_STR, CONST_VALUE_BOOLEAN, TYPE_PART, TYPE_DECL_LIST, TYPE_DEFINITION, TYPE_DECL, SIMPLE_TYPE_DECL_1, SIMPLE_TYPE_DECL_2, SIMPLE_TYPE_DECL_3, ARRAY_RANGE_1, ARRAY_RANGE_2, ARRAY_RANGE_3, ARRAY_RANGE_4,
  ARRAY_TYPE_DECL, RECORD_TYPE_DECL, FIELD_DECL_LIST, FIELD_DECL, NAME_LIST, VAR_PART, VAR_DECL_LIST, VAR_DECL, ROUTINE_PART, 
  FUNCTION_DECL, FUNCTION_HEAD, PROCEDURE_DECL, PROCEDURE_HEAD, PARAMETERS, PARA_DECL_LIST, PARA_TYPE_LIST_1, PARA_TYPE_LIST_2, VAR_PARA_LIST, 
  VAL_PARA_LIST, ROUTINE_BODY, COMPOUND_STMT, STMT_LIST, STMT, NON_LABEL_STMT, ASSIGN_STMT_1, ASSIGN_STMT_2, ASSIGN_STMT_3, PROC_STMT_1, PROC_STMT_2, PROC_STMT_3, PROC_STMT_4, IF_STMT, ELSE_CLAUSE, 
  REPEAT_STMT, WHILE_STMT, FOR_STMT, DIRECTION, CASE_STMT, CASE_EXPR_LIST, CASE_EXPR, GOTO_STMT, EXPRESSION_LIST, EXPRESSION, 
  EXPR, PLUS_EXPR, MINUS_EXPR, OR_EXPR, TERM, MUL_TERM, DIV_TERM, MOD_TERM, AND_TERM, FACTOR_1, FACTOR_2, FACTOR_3, FACTOR_4, FACTOR_5, FACTOR_6, FACTOR_7, FACTOR_8, FACTOR_9, FACTOR_10, ARGS_LIST, SYS_TYPE, SYS_FUNCT, SYS_PROC, SYS_CON
};

typedef struct cstTreeNode cst_node;
typedef cst_node* cst_tree;
struct cstTreeNode {
  int item;
  int node_id;
  cst_tree first;
  cst_tree second;
  cst_tree third;
  cst_tree fourth;
  cst_tree fifth;
};

cst_tree create_node(int ival, int case_id, cst_tree t1, cst_tree t2, cst_tree t3, cst_tree t4, cst_tree t5);


#endif /* !CST_H */
