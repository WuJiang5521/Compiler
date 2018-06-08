//
// Created by WuJiang on 2018/6/8.
//

#include "tree.h"

#ifdef CHECK_SEMANTICS
using namespace ast;

void yyerror(const char *info) {
    fprintf(stderr, "Semantics error: %s\n", s);
    exit(1);
}

// block object
bool Program::checkSemantics() {
    // check children
    is_legal &= define->checkSemantics();
    if (is_legal) is_legal &= body->checkSemantics();
    // check between children
    // check itself
    return is_legal;
}

bool Define::checkSemantics() {
    // check children
    for (LabelDef *iter: label_def)
        is_legal &= iter->checkSemantics();
    for (ConstDef *iter: const_def)
        is_legal &= iter->checkSemantics();
    for (TypeDef *iter: type_def)
        is_legal &= iter->checkSemantics();
    for (VarDef *iter: var_def)
        is_legal &= iter->checkSemantics();
    for (FunctionDef *iter: function_def)
        is_legal &= iter->checkSemantics();
    // check between children
    if(is_legal)
        for (ConstDef *c_iter: const_def) {
            if(is_legal)
                for (TypeDef *t_iter: type_def)
                    if (c_iter->name == t_iter->name) {
                        is_legal = false;
                        break;
                    } else;
            else break;
            if (is_legal)
                for (VarDef *v_iter: var_def)
                    if (c_iter->name == v_iter->name) {
                        is_legal = false;
                        break;
                    } else;
            else break;
            if (is_legal)
                for (FunctionDef *f_iter: function_def)
                    if (c_iter->name == f_iter->name) {
                        is_legal = false;
                        break;
                    } else;
            else break;
        }
    if(is_legal)
        for (TypeDef *t_iter: type_def) {
            if (is_legal)
                for (VarDef *v_iter: var_def)
                    if (t_iter->name == v_iter->name) {
                        is_legal = false;
                        break;
                    } else;
            else break;
            if (is_legal)
                for (FunctionDef *f_iter: function_def)
                    if (t_iter->name == f_iter->name) {
                        is_legal = false;
                        break;
                    } else;
            else break;
        }
    if(is_legal)
        for (VarDef *v_iter: var_def) {
            if (is_legal)
                for (FunctionDef *f_iter: function_def)
                    if (t_iter->name == f_iter->name) {
                        is_legal = false;
                        break;
                    } else;
            else break;
        }
    // check itself
    return is_legal;
}

bool Body::checkSemantics() {
    // check children
    for (Stm *iter: stms)
        is_legal &= iter->checkSemantics();
    // check between children
    // check itself
    return is_legal;
}

bool Situation::checkSemantics() {
    // check children
    for (Exp *iter: match_list)
        is_legal &= iter->checkSemantics();
    is_legal &= solution->checkSemantics();
    // check between children
    // check itself
    return is_legal;
}

// define object
bool LabelDef::checkSemantics() {
    // check children
    // check between children
    // check itself
    is_legal = true;
    return is_legal;
}

bool ConstDef::checkSemantics() {
    // check children
    // check between children
    // check itself
    is_legal = true;
    return is_legal;
}

bool TypeDef::checkSemantics() {
    // check children
    // check between children
    // check itself
    is_legal = true;
    return is_legal;
}

bool VarDef::checkSemantics() {
    // check children
    // check between children
    // check itself
    is_legal = true;
    return is_legal;
}

bool FunctionDef::checkSemantics() {
    // check children
    is_legal &= define->checkSemantics();
    if (is_legal) {
        for (std::string arg_name: args_name)
            if (arg_name == name) {
                is_legal = false;
                break;
            }
        for (ConstDef *iter: const_def)
            is_legal &= iter->checkSemantics();
        for (TypeDef *iter: type_def)
            is_legal &= iter->checkSemantics();
        for (VarDef *iter: var_def)
            is_legal &= iter->checkSemantics();
        for (FunctionDef *iter: function_def)
            is_legal &= iter->checkSemantics();
    }
    // check between children
    // check itself
    return is_legal;
}

// stm
bool AssignStm::checkSemantics() {
    // check children
    // check between children
    // check itself
    return is_legal;
}

bool CallStm::checkSemantics() {
    // check children
    for (Exp *iter: args)
        is_legal &= iter->checkSemantics();
    // check between children
    // check itself
    FunctionDef *function = findFunction(name, this->father);
    if(function == nullptr) is_legal = false;
    else if (args.size() != function->args_type.size()) is_legal = false;
    else {
        for (int i = 0; i < args.size(); i++)
            if (!isSameType(args[i].return_type, function->args_type[i])){
                is_legal = false;
                break;
            }
    }
    return is_legal;
}

bool CaseStm::checkSemantics() {
    // check children
    // check between children
    // check itself
    return is_legal;
}

bool ForStm::checkSemantics() {
    // check children
    // check between children
    // check itself
    return is_legal;
}

bool GotoStm::checkSemantics() {
    // check children
    // check between children
    // check itself
    is_legal &= canFindLabel(label, this->father);
    return is_legal;
}

bool IfStm::checkSemantics() {
    // check children
    is_legal &= condition->checkSemantics();
    is_legal &= true_do->checkSemantics();
    if (false_do != nullptr) is_legal &= false_do->checkSemantics();
    // check between children
    // check itself
    is_legal &= isTypeBoolean(condition->return_type);
    return is_legal;
}

bool LabelStm::checkSemantics() {
    // check children
    // check between children
    // check itself
    is_legal &= canFindLabel(label, this->father);
    return is_legal;
}

bool RepeatStm::checkSemantics() {
    // check children
    is_legal &= condition->checkSemantics();
    is_legal &= loop->checkSemantics();
    // check between children
    // check itself
    is_legal &= isTypeBoolean(condition->return_type);
    return is_legal;
}

bool WhileStm::checkSemantics() {
    // check children
    is_legal &= condition->checkSemantics();
    is_legal &= loop->checkSemantics();
    // check between children
    // check itself
    is_legal &= isTypeBoolean(condition->return_type);
    return is_legal;
}

// exp
bool UnaryExp::checkSemantics() {
    // check children
    // check between children
    // check itself
    return is_legal;
}

bool BinaryExp::checkSemantics() {
    // check children
    // check between children
    // check itself
    return is_legal;
}

bool CallExp::checkSemantics() {
    // check children
    for (Exp *iter: args)
        is_legal &= iter->checkSemantics();
    // check between children
    // check itself
    FunctionDef *function = findFunction(name, this->father);
    if(function == nullptr) is_legal = false;
    else if (args.size() != function->args_type.size()) is_legal = false;
    else {
        for (int i = 0; i < args.size(); i++)
            if (!isSameType(args[i].return_type, function->args_type[i])){
                is_legal = false;
                break;
            }
        if (is_legal) return_type = copyType(function->rtn_type);
    }
    return is_legal;
}

bool ConstantExp::checkSemantics() {
    return_type = generateTypeByValue(value);
    is_legal = true;
    return is_legal;
}

bool VariableExp::checkSemantics() {
    Base *temp = findName(name, this->father);
    if(temp == nullptr) is_legal = false;
    else switch (temp->node_type) {
        case N_CONST_DEF: {
            ConstDef *node = (ConstDef*)temp;
            is_legal = true;
            return_type = node->value->return_type;
            return_value = node->value->return_value;
        } break;
        case N_VAR_DEF: {
            VarDef *node = (VarDef*)temp;
            is_legal = true;
            return_type = node->type;
        } break;
        case N_ARG_DEF: {
            ArgDef *node = (ArgDef*)temp;
            is_legal = true;
            return_type = node->type;
        } break;
        default: is_legal = false;
    }
    return is_legal;
}

#endif
