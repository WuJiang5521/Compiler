/*
 * translator.cpp
 * Copyright (C) 2018 weihao <blackhatdwh@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

/* NOTE:
 * - Most stmt will return Body
 */

#include <cstddef>
#include "translator.h"
#include "spl.tab.h"
#include "cst.h"
#include "tree.h"
#include "common.h"
#include "symtab.h"

std::string lookup_string(int index) {
    extern sym_tab_node symtab[];
    std::string result = symtab[index].id;
    return result;
}

float lookup_float(int index) {
    extern sym_tab_node symtab[];
    char* result = symtab[index].id;
    return atof(result);
}

void set_type(int index, int type) {
    extern sym_tab_node symtab[];
    symtab[index].type = type;
}

int lookup_type(int index) {
    extern sym_tab_node symtab[];
    return symtab[index].type;
}

Base* Translator::translate(cst_tree tree) {
    switch(tree->node_id) {
        case PROGRAM:
        {
            cst_tree program_head_ptr = tree->first;
            std::string head_name = lookup_string(program_head_ptr->item);
            Program* program = new Program(head_name);
            cst_tree routine_head_ptr = tree->second->first;
            Define* define = (Define*)translate(routine_head_ptr);
            program->define = define;
            cst_tree stmt_list_ptr = tree->second->second->first->first;
            Body* body = (Body*)translate(stmt_list_ptr);
            program->body = body;
            return (Base*)program;
        }

        case ROUTINE_HEAD:
        {
            Define* define = new Define();

            // ROUTINE_HEAD->LABEL_PART
            cst_tree label_part_ptr = tree->first;
            if (label_part_ptr->first == nullptr) {
                // no label
            }
            else {
                cst_tree label_list_ptr = label_part_ptr->first;
                while (label_list_ptr->first != nullptr) {
                    LabelDef* labelDef = new LabelDef(label_list_ptr->item);
                    define->addLabel(labelDef);
                    label_list_ptr = label_list_ptr->first;
                }
                LabelDef* labelDef = new LabelDef(label_list_ptr->item);
                define->addLabel(labelDef);
            }
            
            
            // ROUTINE_HEAD->CONST_PART
            cst_tree const_expr_list_ptr = tree->second->first;
            if (const_expr_list_ptr == nullptr) {
                // no const
            }
            else {
                while (const_expr_list_ptr->second != nullptr) {
                    std::string name = lookup_string(const_expr_list_ptr->item);
                    ConstantExp* value = (ConstantExp*)translate(const_expr_list_ptr->second);
                    ConstDef* constDef = new ConstDef(name, value);
                    define->addConst(constDef);
                    set_type(const_expr_list_ptr->item, value->value->base_type);
                    const_expr_list_ptr = const_expr_list_ptr->first;
                }
                std::string name = lookup_string(const_expr_list_ptr->item);
                ConstantExp* value = (ConstantExp*)translate(const_expr_list_ptr->first);
                ConstDef* constDef = new ConstDef(name, value);
                define->addConst(constDef);
                set_type(const_expr_list_ptr->item, value->value->base_type);
            }

            // ROUTINE_HEAD->TYPE_PART
            cst_tree type_decl_list_ptr = tree->third->first;
            if (type_decl_list_ptr == nullptr) {
                // no type definition
            }
            else {
                while (type_decl_list_ptr->second != nullptr) {
                    cst_tree type_definition_ptr = type_decl_list_ptr->second;
                    std::string name = lookup_string(type_definition_ptr->item);
                    Type* type = (Type*)translate(type_definition_ptr->first);
                    TypeDef* typeDef = new TypeDef(name, type);
                    define->addType(typeDef);
                    type_decl_list_ptr = type_decl_list_ptr->first;
                }
                cst_tree type_definition_ptr = type_decl_list_ptr->first;
                std::string name = lookup_string(type_definition_ptr->item);
                Type* type = (Type*)translate(type_definition_ptr->first);
                TypeDef* typeDef = new TypeDef(name, type);
                define->addType(typeDef);
            }

            // ROUTINE_HEAD->VAR_PART
            cst_tree var_decl_list_ptr = tree->fourth->first;
            if (var_decl_list_ptr == nullptr) {
                // no var definition
            }
            else {
                while (var_decl_list_ptr->second != nullptr) {
                    cst_tree var_decl_ptr = var_decl_list_ptr->second;
                    Type* type = (Type*)translate(var_decl_ptr->second);
                    cst_tree name_list_ptr = var_decl_ptr->first;
                     do {
                        std::string name = lookup_string(name_list_ptr->item);
                        VarDef* varDef = new VarDef(name, type);

                        set_type(name_list_ptr->item, type->base_type);

                        define->addVar(varDef);
                        name_list_ptr = name_list_ptr->first;
                    } while (name_list_ptr != nullptr);

                    var_decl_list_ptr = var_decl_list_ptr->first;
                }
                cst_tree var_decl_ptr = var_decl_list_ptr->first;
                Type* type = (Type*)translate(var_decl_ptr->second);
                cst_tree name_list_ptr = var_decl_ptr->first;
                do {
                    std::string name = lookup_string(name_list_ptr->item);
                    VarDef* varDef = new VarDef(name, type);

                    set_type(name_list_ptr->item, type->base_type);

                    define->addVar(varDef);
                    name_list_ptr = name_list_ptr->first;
                } while (name_list_ptr != nullptr);
            }

            // ROUTINE_HEAD->ROUTINE_PART
            cst_tree routine_part_ptr = tree->fifth;
            if (routine_part_ptr->first == nullptr) {
                // empty
            }
            else {
                while (routine_part_ptr->second != nullptr) {
                    cst_tree function_decl_ptr = routine_part_ptr->second;
                    cst_tree function_head_ptr = function_decl_ptr->first;
                    std::string name = lookup_string(function_head_ptr->item);
                    FunctionDef* functionDef = new FunctionDef(name);
                    cst_tree parameters_ptr = function_head_ptr->first;
                    if (parameters_ptr->first == nullptr) {
                        // no parameter
                    }
                    else {
                        cst_tree para_decl_list_ptr = parameters_ptr->first;
                        while (para_decl_list_ptr->second != nullptr) {
                            cst_tree para_type_list_ptr = para_decl_list_ptr->second;
                            cst_tree simple_type_decl_ptr = para_type_list_ptr->second;
                            Type* type = (Type*)translate(simple_type_decl_ptr);
                            if (para_type_list_ptr->node_id == PARA_TYPE_LIST_1) {
                                cst_tree var_para_list_ptr = para_type_list_ptr->first;
                                cst_tree name_list_ptr = var_para_list_ptr->first;
                                do {
                                    std::string name = lookup_string(name_list_ptr->item);
                                    functionDef->addArgs(name, type, true);
                                    name_list_ptr = name_list_ptr->first;
                                } while (name_list_ptr != nullptr);

                            }
                            else if (para_type_list_ptr->node_id == PARA_TYPE_LIST_2) {
                                cst_tree val_para_list_ptr = para_type_list_ptr->first;
                                cst_tree name_list_ptr = val_para_list_ptr->first;
                                do {
                                    std::string name = lookup_string(name_list_ptr->item);
                                    functionDef->addArgs(name, type, false);
                                    name_list_ptr = name_list_ptr->first;
                                } while (name_list_ptr != nullptr);
                            }
                            para_decl_list_ptr = para_decl_list_ptr->first;
                        }
                        cst_tree para_type_list_ptr = para_decl_list_ptr->first;
                        cst_tree simple_type_decl_ptr = para_type_list_ptr->second;
                        Type* type = (Type*)translate(simple_type_decl_ptr);
                        if (para_type_list_ptr->node_id == PARA_TYPE_LIST_1) {
                            cst_tree var_para_list_ptr = para_type_list_ptr->first;
                            cst_tree name_list_ptr = var_para_list_ptr->first;
                            do {
                                std::string name = lookup_string(name_list_ptr->item);
                                functionDef->addArgs(name, type, true);
                                name_list_ptr = name_list_ptr->first;
                            } while (name_list_ptr != nullptr);

                        }
                        else if (para_type_list_ptr->node_id == PARA_TYPE_LIST_2) {
                            cst_tree val_para_list_ptr = para_type_list_ptr->first;
                            cst_tree name_list_ptr = val_para_list_ptr->first;
                            do {
                                std::string name = lookup_string(name_list_ptr->item);
                                functionDef->addArgs(name, type, false);
                                name_list_ptr = name_list_ptr->first;
                            } while (name_list_ptr != nullptr);
                        }
                    }
                    if (function_head_ptr->second != nullptr) {
                        Type* type = (Type*)translate(function_head_ptr->second);
                        functionDef->setReturnType(type);
                    }
                    else {
                        // procedure, no return type
                    }
                    // function body
                    cst_tree sub_routine_ptr = function_decl_ptr->second;
                    cst_tree routine_head_ptr = sub_routine_ptr->first;
                    Define* func_define = (Define*)translate(routine_head_ptr);
                    cst_tree stmt_list_ptr = sub_routine_ptr->second->first->first;
                    functionDef->addDefine(func_define);
                    functionDef->body = (Body*)translate(stmt_list_ptr);

                    define->addFunction(functionDef);

                    routine_part_ptr = routine_part_ptr->first;
                }
                cst_tree function_decl_ptr = routine_part_ptr->first;
                cst_tree function_head_ptr = function_decl_ptr->first;
                std::string name = lookup_string(function_head_ptr->item);
                FunctionDef* functionDef = new FunctionDef(name);
                cst_tree parameters_ptr = function_head_ptr->first;
                if (parameters_ptr->first == nullptr) {
                    // no parameter
                }
                else {
                    cst_tree para_decl_list_ptr = parameters_ptr->first;
                    while (para_decl_list_ptr->second != nullptr) {
                        cst_tree para_type_list_ptr = para_decl_list_ptr->second;
                        cst_tree simple_type_decl_ptr = para_type_list_ptr->second;
                        Type* type = (Type*)translate(simple_type_decl_ptr);
                        if (para_type_list_ptr->node_id == PARA_TYPE_LIST_1) {
                            cst_tree var_para_list_ptr = para_type_list_ptr->first;
                            cst_tree name_list_ptr = var_para_list_ptr->first;
                            do {
                                std::string name = lookup_string(name_list_ptr->item);
                                functionDef->addArgs(name, type, true);
                                name_list_ptr = name_list_ptr->first;
                            } while (name_list_ptr != nullptr);

                        }
                        else if (para_type_list_ptr->node_id == PARA_TYPE_LIST_2) {
                            cst_tree val_para_list_ptr = para_type_list_ptr->first;
                            cst_tree name_list_ptr = val_para_list_ptr->first;
                            do {
                                std::string name = lookup_string(name_list_ptr->item);
                                functionDef->addArgs(name, type, false);
                                name_list_ptr = name_list_ptr->first;
                            } while (name_list_ptr != nullptr);
                        }
                        para_decl_list_ptr = para_decl_list_ptr->first;
                    }
                    cst_tree para_type_list_ptr = para_decl_list_ptr->first;
                    cst_tree simple_type_decl_ptr = para_type_list_ptr->second;
                    Type* type = (Type*)translate(simple_type_decl_ptr);
                    if (para_type_list_ptr->node_id == PARA_TYPE_LIST_1) {
                        cst_tree var_para_list_ptr = para_type_list_ptr->first;
                        cst_tree name_list_ptr = var_para_list_ptr->first;
                        do {
                            std::string name = lookup_string(name_list_ptr->item);
                            functionDef->addArgs(name, type, true);
                            name_list_ptr = name_list_ptr->first;
                        } while (name_list_ptr != nullptr);

                    }
                    else if (para_type_list_ptr->node_id == PARA_TYPE_LIST_2) {
                        cst_tree val_para_list_ptr = para_type_list_ptr->first;
                        cst_tree name_list_ptr = val_para_list_ptr->first;
                        do {
                            std::string name = lookup_string(name_list_ptr->item);
                            functionDef->addArgs(name, type, false);
                            name_list_ptr = name_list_ptr->first;
                        } while (name_list_ptr != nullptr);
                    }
                }
                if (function_head_ptr->second != nullptr) {
                    Type* type = (Type*)translate(function_head_ptr->second);
                    functionDef->setReturnType(type);
                }
                else {
                    // procedure, no return type
                }
                // function body
                cst_tree sub_routine_ptr = function_decl_ptr->second;
                cst_tree routine_head_ptr = sub_routine_ptr->first;
                Define* func_define = (Define*)translate(routine_head_ptr);
                cst_tree stmt_list_ptr = sub_routine_ptr->second->first->first;
                functionDef->addDefine(func_define);
                functionDef->body = (Body*)translate(stmt_list_ptr);

                define->addFunction(functionDef);

                routine_part_ptr = routine_part_ptr->first;
            }
            return (Base*)define;
        }


        case SYS_TYPE:
        {
            Type* type = new Type();
            switch (tree->item) {
                case T_CHAR:
                    type->base_type = 2;
                    return (Base*)type;
                case T_INTEGER:
                    type->base_type = 0;
                    return (Base*)type;
                case T_REAL:
                    type->base_type = 1;
                    return (Base*)type;
                case T_BOOLEAN:
                    type->base_type = 3;
                    return (Base*)type;
            }
        }

        case SIMPLE_TYPE_DECL_1:
        {
            return (Base*)translate(tree->first);
        }

        // user defined type
        case SIMPLE_TYPE_DECL_2:
        {
            //Type* type = findType(lookup_string(tree->item), tree);
            //return (Base*)type;
        }

        case SIMPLE_TYPE_DECL_3:
        {
            // TODO what's this?
        }

        case TYPE_DECL:
        {
            return (Base*)translate(tree->first);
        }

        case ARRAY_TYPE_DECL:
        {
            Type* element_type = (Type*)translate(tree->second);
            cst_tree simple_type_decl_ptr = tree->first;
            Type* array_type = new Type();
            int first_value = 0;
            int second_value = 0;
            switch (simple_type_decl_ptr->node_id) {
                case ARRAY_RANGE_1:
                    first_value = ((Value*)translate(simple_type_decl_ptr->first))->val.integer_value;
                    second_value = ((Value*)translate(simple_type_decl_ptr->second))->val.integer_value;
                    break;
                case ARRAY_RANGE_2:
                    first_value = -1 * ((Value*)translate(simple_type_decl_ptr->first))->val.integer_value;
                    second_value = ((Value*)translate(simple_type_decl_ptr->second))->val.integer_value;
                    break;
                case ARRAY_RANGE_3:
                    first_value = -1 * ((Value*)translate(simple_type_decl_ptr->first))->val.integer_value;
                    second_value = -1 * ((Value*)translate(simple_type_decl_ptr->second))->val.integer_value;
                    break;
                case ARRAY_RANGE_4:
                    // TODO a[b..c]
                    break;
            }

            array_type->array_start = first_value;
            array_type->array_end = second_value;
            array_type->base_type = 5;

            //addType(array_type);

            return (Base*)array_type;
        }

        case RECORD_TYPE_DECL:
        {
            Type* type = new Type();
            type->base_type = 6;
            cst_tree field_decl_list_ptr = tree->first;
            while (field_decl_list_ptr->second != nullptr) {
                cst_tree field_decl_ptr = field_decl_list_ptr->second;
                cst_tree name_list_ptr = field_decl_ptr->first;
                cst_tree type_decl_ptr = field_decl_ptr->second;
                Type* tmp_type = (Type*)translate(type_decl_ptr);
                while (name_list_ptr->first != nullptr) {
                    std::string name = lookup_string(name_list_ptr->item);
                    //type->child_type
                    name_list_ptr = name_list_ptr->first;
                }
                field_decl_list_ptr = field_decl_list_ptr->first;
            }
            return (Base*)type;
        }

        case STMT:
        {
            Body* body = new Body();
            cst_tree stmt_ptr = tree;
            // no label
            if (stmt_ptr->item == NOTHING) {
                // do nothing
            }
            // has label
            else {
                int label = stmt_ptr->item;
                LabelStm* labelStm = new LabelStm(label);
                body->addStm(labelStm);
            }
            cst_tree non_label_stmt_ptr = stmt_ptr->first;
            Body* tmp_body = (Body*)translate(non_label_stmt_ptr);
            for(std::vector<Stm*>::iterator it = tmp_body->stms.begin(); it != tmp_body->stms.end(); it++) {
                body->addStm(*it);
            }

            return (Base*)body;
        }


        case STMT_LIST:
        {
            Body* body = new Body();
            cst_tree stmt_list_ptr = tree;
            if (stmt_list_ptr->first == nullptr) {
                // empty
            }
            else {
                while (stmt_list_ptr->first != nullptr) {
                    cst_tree stmt_ptr = stmt_list_ptr->second;
                    Body* tmp_body = (Body*)translate(stmt_ptr);
                    for(std::vector<Stm*>::iterator it = tmp_body->stms.begin(); it != tmp_body->stms.end(); it++) {
                        body->addStm(*it);
                    }
                    stmt_list_ptr = stmt_list_ptr->first;
                }
            }
            return (Base*)body;
        }

        case NON_LABEL_STMT:
        {
            Body* body = (Body*)translate(tree->first);
            return (Base*)body;
        }

        case ASSIGN_STMT_1:
        {
            // example: a = 3
            Body* body = new Body();
            std::string name = lookup_string(tree->item);
            Exp* left_value = new VariableExp(name);
            Exp* right_value = (Exp*)translate(tree->first);
            AssignStm* assignStm = new AssignStm(left_value, right_value);
            body->addStm(assignStm);
            return (Base*)body;
        }

        case ASSIGN_STMT_2:
        {
            // example: a[1] = 3
            Body* body = new Body();
            std::string name = lookup_string(tree->item);
            Exp* left_value_1 = new VariableExp(name);
            Exp* left_value_2 = (Exp*)translate(tree->first);
            BinaryExp* left_value = new BinaryExp(OP_INDEX, left_value_1, left_value_2);
            Exp* right_value = (Exp*)translate(tree->second);
            AssignStm* assignStm = new AssignStm(left_value, right_value);
            body->addStm(assignStm);
            return (Base*)body;
        }

        case ASSIGN_STMT_3:
        {
            // example: a.b = 3
            Body* body = new Body();
            std::string name_1 = lookup_string(tree->item);
            Exp* left_value_1 = new VariableExp(name_1);
            std::string name_2 = lookup_string(tree->first->item);
            Exp* left_value_2 = new VariableExp(name_2);
            BinaryExp* left_value = new BinaryExp(OP_DOT, left_value_1, left_value_2);

            Exp* right_value = (Exp*)translate(tree->second);

            AssignStm* assignStm = new AssignStm(left_value, right_value);
            body->addStm(assignStm);
            return (Base*)body;
        }

        case PROC_STMT_1:
        {
            Body* body = new Body();
            std::string name = lookup_string(tree->item);
            CallStm* callStm = new CallStm(name);
            body->addStm(callStm);
            return (Base*)body;
        }

        case PROC_STMT_2:
        {
            Body* body = new Body();
            std::string name = lookup_string(tree->item);
            CallStm* callStm = new CallStm(name);
            ExpList* expList = (ExpList*)translate(tree->first);

            for(std::vector<Exp*>::iterator it = expList->exps.begin(); it != expList->exps.end(); it++) {
                callStm->addArgs(*it);
            }

            body->addStm(callStm);
            return (Base*)body;
        }

        case PROC_STMT_3:
        {
            Body* body = new Body();
            CallStm* callStm = (CallStm*)translate(tree->first);
            ExpList* expList = (ExpList*)translate(tree->second);

            for(std::vector<Exp*>::iterator it = expList->exps.begin(); it != expList->exps.end(); it++) {
                callStm->addArgs(*it);
            }

            body->addStm(callStm);

            return (Base*)body;
        }

        case PROC_STMT_4:
        {
            Body* body = new Body();
            CallStm* callStm = (CallStm*)translate(tree->first);
            Exp* exp = (Exp*)translate(tree->second);
            callStm->addArgs(exp);

            body->addStm(callStm);

            return (Base*)body;
        }

        case SYS_PROC:
        {
            CallStm* callStm = nullptr;
            switch (tree->item) {
                case T_WRITE:
                    callStm = new CallStm("write");
                    break;
                case T_WRITELN:
                    callStm = new CallStm("writeln");
                    break;
                case T_READ:
                    callStm = new CallStm("read");
                    break;
            }
            return callStm;
        }

        case COMPOUND_STMT:
        {
            Body* body = (Body*)translate(tree->first);
            return body;
        }

        case IF_STMT:
        {
            Body* body = new Body();

            Exp* condition = (Exp*)translate(tree->first);
            Body* true_do = (Body*)translate(tree->second);
            Body* false_do = (Body*)translate(tree->third);

            IfStm* ifStm = new IfStm();
            ifStm->condition = condition;
            ifStm->true_do = true_do;
            ifStm->false_do = false_do;

            body->addStm(ifStm);
            return (Base*)body;
        }

        case ELSE_CLAUSE:
        {
            Body* body = new Body();
            if (tree->first == nullptr) {
                // null
            }
            else {
                body = (Body*)translate(tree->first);
            }
            return (Base*)body;
        }

        case REPEAT_STMT:
        {
            Body* body = new Body();

            Exp* condition = (Exp*)translate(tree->second);

            RepeatStm* repeatStm = new RepeatStm();
            repeatStm->condition = condition;
            cst_tree stmt_list_ptr = tree->first;
            Body* tmp_body = (Body*)translate(stmt_list_ptr);
            repeatStm->loop = tmp_body;
            body->addStm(repeatStm);
            return (Base*)repeatStm;
        }

        case WHILE_STMT:
        {
            Body* body = new Body();

            Exp* condition = (Exp*)translate(tree->first);
            WhileStm* whileStm = new WhileStm(condition);
            cst_tree stmt_ptr = tree->second;
            whileStm->loop = (Body*)translate(stmt_ptr);
            body->addStm(whileStm);

            return (Base*)body;
        }

        case FOR_STMT:
        {
            Body* body = new Body();
            std::string iter = lookup_string(tree->item);
            Exp* start = (Exp*)translate(tree->first);
            Exp* end = (Exp*)translate(tree->third);
            int step = 0;
            cst_tree direction_ptr = tree->second;
            if (direction_ptr->item == T_TO) {
                step = 1;
            }
            else {
                step = -1;
            }
            ForStm* forStm = new ForStm(iter, start, end, step);
            forStm->loop = (Body*)translate(tree->fourth);
            body->addStm(forStm);
            return (Base*)body;
        }

        case CASE_STMT:
        {
            Body* body = new Body();

            Exp* object = (Exp*)translate(tree->first);
            CaseStm* caseStm = new CaseStm(object);

            cst_tree case_expr_list_ptr = tree->second;
            while (case_expr_list_ptr->second != nullptr) {
                cst_tree case_expr_ptr = case_expr_list_ptr->second;
                Situation* situation = (Situation*)translate(case_expr_ptr);
                caseStm->addSituation(situation);
                case_expr_list_ptr = case_expr_list_ptr->first;
            }
            cst_tree case_expr_ptr = case_expr_list_ptr->first;
            Situation* situation = (Situation*)translate(case_expr_ptr);
            caseStm->addSituation(situation);

            body->addStm(caseStm);

            return (Base*)body;
        }

        case CASE_EXPR:
        {
            Situation* situation = new Situation();
            if (tree->second != nullptr) {
                situation->solution = (Body*)translate(tree->second);
                Exp* exp = (ConstantExp*)translate(tree->first);
                situation->addMatch(exp);
                return situation;
            }
            else {
                situation->solution = (Body*)translate(tree->first);
                std::string name = lookup_string(tree->item);
                Exp* exp = new VariableExp(name);
                situation->addMatch(exp);
                return situation;
            }
        }

        case GOTO_STMT:
        {
            Body* body = new Body();
            int label = tree->item;
            GotoStm* gotoStm = new GotoStm(label);
            body->addStm(gotoStm);
            return (Base*)gotoStm;
        }

        case PLUS_EXPR:
        {
            Exp* exp_1 = (Exp*)translate(tree->first);
            Exp* exp_2 = (Exp*)translate(tree->second);
            BinaryExp* binaryExp = new BinaryExp(OP_ADD, exp_1, exp_2);
            return (Base*)binaryExp;
        }

        case MINUS_EXPR:
        {
            Exp* exp_1 = (Exp*)translate(tree->first);
            Exp* exp_2 = (Exp*)translate(tree->second);
            BinaryExp* binaryExp = new BinaryExp(OP_MINUS, exp_1, exp_2);
            return (Base*)binaryExp;
        }

        case OR_EXPR:
        {
            Exp* exp_1 = (Exp*)translate(tree->first);
            Exp* exp_2 = (Exp*)translate(tree->second);
            BinaryExp* binaryExp = new BinaryExp(OP_OR, exp_1, exp_2);
            return (Base*)binaryExp;
        }

        case EXPR:
        {
            Exp* exp_1 = (Exp*)translate(tree->first);
            return (Base*)exp_1;
        }

        case MUL_TERM:
        {
            Exp* exp_1 = (Exp*)translate(tree->first);
            Exp* exp_2 = (Exp*)translate(tree->second);
            BinaryExp* binaryExp = new BinaryExp(OP_MULTI, exp_1, exp_2);
            return (Base*)binaryExp;
        }

        case DIV_TERM:
        {
            Exp* exp_1 = (Exp*)translate(tree->first);
            Exp* exp_2 = (Exp*)translate(tree->second);
            BinaryExp* binaryExp = new BinaryExp(OP_RDIV, exp_1, exp_2);
            return (Base*)binaryExp;
        }

        case MOD_TERM:
        {
            Exp* exp_1 = (Exp*)translate(tree->first);
            Exp* exp_2 = (Exp*)translate(tree->second);
            BinaryExp* binaryExp = new BinaryExp(OP_MOD, exp_1, exp_2);
            return (Base*)binaryExp;
        }

        case AND_TERM:
        {
            Exp* exp_1 = (Exp*)translate(tree->first);
            Exp* exp_2 = (Exp*)translate(tree->second);
            BinaryExp* binaryExp = new BinaryExp(OP_AND, exp_1, exp_2);
            return (Base*)binaryExp;
        }

        case TERM:
        {
            Exp* exp_1 = (Exp*)translate(tree->first);
            return (Base*)exp_1;
        }

        case FACTOR_1:
        {
            std::string name = lookup_string(tree->item);
            Exp* exp_1 = new VariableExp(name);
            return (Base*)exp_1;
        }

        case FACTOR_2:
        {
            std::string name = lookup_string(tree->item);
            Exp* exp_1 = new CallExp(name);
            cst_tree args_list_ptr = tree->first;
            while (args_list_ptr->second != nullptr) {
                Exp* tmp_exp = (Exp*)translate(args_list_ptr->second);
                ((CallExp*)exp_1)->addArgs(tmp_exp);
                args_list_ptr = args_list_ptr->first;
            }
            Exp* tmp_exp = (Exp*)translate(args_list_ptr->first);
            ((CallExp*)exp_1)->addArgs(tmp_exp);
            return (Base*)exp_1;
        }

        case FACTOR_3:
        {
            CallExp* callExp = (CallExp*)translate(tree->first);
            return (Base*)callExp;
        }

        case FACTOR_4:
        {
            CallExp* callExp = (CallExp*)translate(tree->first);
            ExpList* expList = (ExpList*)translate(tree->second);
            for(std::vector<Exp*>::iterator it = expList->exps.begin(); it != expList->exps.end(); it++) {
                callExp->addArgs(*it);
            }
            return (Base*)callExp;
        }

        case FACTOR_5:
        {
            return (Base*)translate(tree->first);
        }

        case FACTOR_6:
        {
            return (Base*)translate(tree->first);
        }

        case FACTOR_7:
        {
            Exp* tmp_exp = (Exp*)translate(tree->first);
            Exp* exp_1 = new UnaryExp(OP_NOT, tmp_exp);
            return (Base*)exp_1;
        }

        case FACTOR_8:
        {
            Exp* tmp_exp = (Exp*)translate(tree->first);
            Exp* exp_1 = new UnaryExp(OP_MINUS, tmp_exp);
            return (Base*)exp_1;
        }

        case FACTOR_9:
        {
            std::string name = lookup_string(tree->item);
            CallExp* callExp = new CallExp(name);
            Exp* exp = (Exp*)translate(tree->first);
            callExp->addArgs(exp);
            return (Base*)callExp;
        }

        case FACTOR_10:
        {
            std::string name_1 = lookup_string(tree->item);
            VariableExp* variableExp_1 = new VariableExp(name_1);
            std::string name_2 = lookup_string(tree->first->item);
            VariableExp* variableExp_2 = new VariableExp(name_2);
            BinaryExp* binaryExp = new BinaryExp(T_DOT, variableExp_1, variableExp_2);
            return (Base*)binaryExp;
        }

        case CONST_VALUE_INT:
        {
            Value* value = new Value;
            value->base_type = 0;
            value->val.integer_value = tree->item;

            return new ConstantExp(value);
        }

        case CONST_VALUE_REAL:
        {
            Value* value = new Value;
            value->base_type = 1;
            value->val.real_value = lookup_float(tree->item);
            return new ConstantExp(value);
        }

        case CONST_VALUE_CHAR:
        {
            Value* value = new Value;
            value->base_type = 2;
            value->val.char_value = lookup_string(tree->item).c_str()[0];
            return new ConstantExp(value);
        }

        case CONST_VALUE_STR:
        {
            Value* value = new Value;
            value->base_type = 4;

            value->val.string_value = new std::string;
            *value->val.string_value = lookup_string(tree->item);
            return new ConstantExp(value);
        }

        case CONST_VALUE:
        {
            Value* value = new Value;
            switch (tree->item) {
                case T_TRUE:
                    value->val.boolean_value = true;
                    value->base_type = 3;
                    break;
                case T_FALSE:
                    value->val.boolean_value = false;
                    value->base_type = 3;
                    break;
                case T_MAXINT:
                    value->val.integer_value = 32767;
                    value->base_type = 0;
                    break;
            }
        }

        case EXPRESSION_LIST:
        {
            ExpList* expList = new ExpList();
            cst_tree expression_list_ptr = tree;
            while (expression_list_ptr->second != nullptr) {
                Exp* exp = (Exp*)translate(expression_list_ptr->second);
                expList->addExp(exp);
                expression_list_ptr = expression_list_ptr->first;
            }
            Exp* exp = (Exp*)translate(expression_list_ptr->first);
            expList->addExp(exp);
        }

        case EXPRESSION:
        {
            if (tree->item != NOTHING) {
                Exp* exp_1 = (Exp*)translate(tree->first);
                Exp* exp_2 = (Exp*)translate(tree->second);
                BinaryExp* binaryExp = nullptr;
                switch (tree->item) {
                    case T_GE:
                        binaryExp = new BinaryExp(T_GE, exp_1, exp_2);
                        break;
                    case T_GT:
                        binaryExp = new BinaryExp(T_GT, exp_1, exp_2);
                        break;
                    case T_LE:
                        binaryExp = new BinaryExp(T_LE, exp_1, exp_2);
                        break;
                    case T_LT:
                        binaryExp = new BinaryExp(T_LT, exp_1, exp_2);
                        break;
                    case T_EQUAL:
                        binaryExp = new BinaryExp(T_EQUAL, exp_1, exp_2);
                        break;
                    case T_NE:
                        binaryExp = new BinaryExp(T_NE, exp_1, exp_2);
                        break;
                }
                return binaryExp;
            }
            else {
                Exp* exp = (Exp*)translate(tree->first);
                return exp;
            }
        }

        case ARGS_LIST:
        {
            ExpList* expList = new ExpList();
            cst_tree args_list_ptr = tree;
            while (args_list_ptr->second != nullptr) {
                Exp* exp = (Exp*)translate(args_list_ptr->second);
                expList->addExp(exp);
                args_list_ptr = args_list_ptr->first;
            }
            Exp* exp = (Exp*)translate(args_list_ptr->first);
            expList->addExp(exp);
            return expList;
        }

        case SYS_FUNCT:
        {
            CallExp* callExp = nullptr;
            switch (tree->item) {
                case T_ABS:
                    callExp = new CallExp("T_ABS");
                    break;
                case T_CHR:
                    callExp = new CallExp("T_CHR");
                    break;
                case T_ODD:
                    callExp = new CallExp("T_ODD");
                    break;
                case T_ORD:
                    callExp = new CallExp("T_ORD");
                    break;
                case T_PRED:
                    callExp = new CallExp("T_PRED");
                    break;
                case T_SQR:
                    callExp = new CallExp("T_SQR");
                    break;
                case T_SQRT:
                    callExp = new CallExp("T_SQRT");
                    break;
                case T_SUCC:
                    callExp = new CallExp("T_SUCC");
                    break;
            }
            return (Base*)callExp;
        }

    }
}

