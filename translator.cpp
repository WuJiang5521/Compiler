/*
 * translator.cpp
 * Copyright (C) 2018 weihao <blackhatdwh@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

/* NOTE:
 * - All stmt will return Body
 */

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
                    Exp* value = (Exp*)translate(const_expr_list_ptr->second);
                    ConstDef* constDef = new ConstDef(name, value);
                    define->addConst(constDef);
                    set_type(const_expr_list_ptr->item, value->return_type->base_type);
                    const_expr_list_ptr = const_expr_list_ptr->first;
                }
                std::string name = lookup_string(const_expr_list_ptr->item);
                Exp* value = (Exp*)translate(const_expr_list_ptr->first);
                ConstDef* constDef = new ConstDef(name, value);
                define->addConst(constDef);
                set_type(const_expr_list_ptr->item, value->return_type->base_type);
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
            if (var_decl_list_ptr != nullptr) {
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
                    } while (name_list_ptr->first != nullptr);

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
                } while (name_list_ptr->first != nullptr);

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
                            // TODO true / false maybe inverted!!
                            if (para_type_list_ptr->node_id == PARA_TYPE_LIST_1) {
                                cst_tree var_para_list_ptr = para_type_list_ptr->first;
                                cst_tree name_list_ptr = var_para_list_ptr->first;
                                do {
                                    std::string name = lookup_string(name_list_ptr->item);
                                    functionDef->addArgs(name, type, false);
                                    name_list_ptr = name_list_ptr->first;
                                } while (name_list_ptr->first != nullptr);

                            }
                            else if (para_type_list_ptr->node_id == PARA_TYPE_LIST_2) {
                                cst_tree val_para_list_ptr = para_type_list_ptr->first;
                                cst_tree name_list_ptr = val_para_list_ptr->first;
                                do {
                                    std::string name = lookup_string(name_list_ptr->item);
                                    functionDef->addArgs(name, type, true);
                                    name_list_ptr = name_list_ptr->first;
                                } while (name_list_ptr->first != nullptr);
                            }
                            para_decl_list_ptr = para_decl_list_ptr->first;
                        }
                        cst_tree para_type_list_ptr = para_decl_list_ptr->first;
                        cst_tree simple_type_decl_ptr = para_type_list_ptr->second;
                        Type* type = (Type*)translate(simple_type_decl_ptr);
                        // TODO true / false maybe inverted!!
                        if (para_type_list_ptr->node_id == PARA_TYPE_LIST_1) {
                            cst_tree var_para_list_ptr = para_type_list_ptr->first;
                            cst_tree name_list_ptr = var_para_list_ptr->first;
                            do {
                                std::string name = lookup_string(name_list_ptr->item);
                                functionDef->addArgs(name, type, false);
                                name_list_ptr = name_list_ptr->first;
                            } while (name_list_ptr->first != nullptr);

                        }
                        else if (para_type_list_ptr->node_id == PARA_TYPE_LIST_2) {
                            cst_tree val_para_list_ptr = para_type_list_ptr->first;
                            cst_tree name_list_ptr = val_para_list_ptr->first;
                            do {
                                std::string name = lookup_string(name_list_ptr->item);
                                functionDef->addArgs(name, type, true);
                                name_list_ptr = name_list_ptr->first;
                            } while (name_list_ptr->first != nullptr);
                        }
                    }
                    Type* type = (Type*)translate(function_head_ptr->second);
                    functionDef->setReturnType(type);

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
                        // TODO true / false maybe inverted!!
                        if (para_type_list_ptr->node_id == PARA_TYPE_LIST_1) {
                            cst_tree var_para_list_ptr = para_type_list_ptr->first;
                            cst_tree name_list_ptr = var_para_list_ptr->first;
                            do {
                                std::string name = lookup_string(name_list_ptr->item);
                                functionDef->addArgs(name, type, false);
                                name_list_ptr = name_list_ptr->first;
                            } while (name_list_ptr->first != nullptr);

                        }
                        else if (para_type_list_ptr->node_id == PARA_TYPE_LIST_2) {
                            cst_tree val_para_list_ptr = para_type_list_ptr->first;
                            cst_tree name_list_ptr = val_para_list_ptr->first;
                            do {
                                std::string name = lookup_string(name_list_ptr->item);
                                functionDef->addArgs(name, type, true);
                                name_list_ptr = name_list_ptr->first;
                            } while (name_list_ptr->first != nullptr);
                        }
                        para_decl_list_ptr = para_decl_list_ptr->first;
                    }
                    cst_tree para_type_list_ptr = para_decl_list_ptr->first;
                    cst_tree simple_type_decl_ptr = para_type_list_ptr->second;
                    Type* type = (Type*)translate(simple_type_decl_ptr);
                    // TODO true / false maybe inverted!!
                    if (para_type_list_ptr->node_id == PARA_TYPE_LIST_1) {
                        cst_tree var_para_list_ptr = para_type_list_ptr->first;
                        cst_tree name_list_ptr = var_para_list_ptr->first;
                        do {
                            std::string name = lookup_string(name_list_ptr->item);
                            functionDef->addArgs(name, type, false);
                            name_list_ptr = name_list_ptr->first;
                        } while (name_list_ptr->first != nullptr);

                    }
                    else if (para_type_list_ptr->node_id == PARA_TYPE_LIST_2) {
                        cst_tree val_para_list_ptr = para_type_list_ptr->first;
                        cst_tree name_list_ptr = val_para_list_ptr->first;
                        do {
                            std::string name = lookup_string(name_list_ptr->item);
                            functionDef->addArgs(name, type, true);
                            name_list_ptr = name_list_ptr->first;
                        } while (name_list_ptr->first != nullptr);
                    }
                }
                Type* type = (Type*)translate(function_head_ptr->second);
                functionDef->setReturnType(type);

                define->addFunction(functionDef);
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

        // only used in translating sys_type
        case SIMPLE_TYPE_DECL:
        {
            return (Base*)translate(tree->first);
        }

        case TYPE_DECL:
        {
            return (Base*)translate(tree->first);
        }

        case ARRAY_TYPE_DECL:
        {
            Type* type = (Type*)translate(tree->second);
            cst_tree simple_type_decl_ptr = tree->first;
            //type->array_start = 
            // TODO
            return (Base*)type;
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

        case ASSIGN_STMT:
        {
            // TODO only support a=3, doesn't support a[10]=3, a.b=1
            Body* body = new Body();
            std::string name = lookup_string(tree->item);
            Exp* right_value = (Exp*)translate(tree->first);
            AssignStm* assignStm = new AssignStm(name, right_value);
            body->addStm(assignStm);
            return (Base*)body;
        }

        case PROC_STMT:
        {
            // TODO
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
            // TODO
        }

        case FACTOR_4:
        {
            // TODO
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
            // TODO
        }

        case FACTOR_10:
        {
            // TODO
        }

        case CONST_VALUE_INT:
        {
            Value* value = new Value();
            value->base_type = 0;
            value->val.integer_value = tree->item;
            return new ConstantExp(value);
        }

        case CONST_VALUE_REAL:
        {
            Value* value = new Value();
            value->base_type = 1;
            value->val.real_value = lookup_float(tree->item);
            return new ConstantExp(value);
        }

        case CONST_VALUE_CHAR:
        {
            Value* value = new Value();
            value->base_type = 2;
            value->val.char_value = lookup_string(tree->item).c_str()[0];
            return new ConstantExp(value);
        }

        case CONST_VALUE_BOOLEAN:
        {
            Value* value = new Value();
            value->base_type = 4;
            // TODO
            return new ConstantExp(value);
        }
    }
}

