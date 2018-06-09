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

bool canFillTypeWithValue(Type *type, Value *value) {
    switch (type->base_type) {
        case TY_REAL:
            return value->base_type == TY_INTEGER || value->base_type == TY_REAL;
        case TY_INTEGER:
        case TY_CHAR:
        case TY_BOOLEAN:
            return value->base_type == type->base_type;
        case TY_STRING:
            return value->base_type == TY_CHAR || value->base_type == TY_STRING;
        case TY_ARRAY:
            if (value->base_type != TY_ARRAY) return false;
            if (type->array_end - type->array_start + 1 != (*(value->val.children_value)).size()) return false;
            for (int i = 0; i <= type->array_end - type->array_start; i++)
                if (!canFillTypeWithValue(type->child_type[i], (*(value->val.children_value))[i])) return false;
            return true;
        case TY_RECORD:
            if (value->base_type != TY_RECORD) return false;
            if (type->child_type.size() != (*(value->val.children_value)).size()) return false;
            for (int i = 0; i < type->child_type.size(); i++)
                if (!canFillTypeWithValue(type->child_type[0], (*(value->val.children_value))[i])) return false;
            return true;
        default:
            if (type->base_type == TY_SET || type->base_type >= type_list.size()) return false;
            return canFillTypeWithValue(type_list[type->base_type], value);
    }
}

bool isTypeBoolean(Type *type) {
    if (type->base_type == TY_BOOLEAN) return true;
    else if (type->base_type >= TY_CUSTOM) return isTypeBoolean(type_list[type->base_type]);
    else return false;
}

bool isTypeInt(Type *type) {
    if (type->base_type == TY_INTEGER) return true;
    else if (type->base_type >= TY_CUSTOM) return isTypeInt(type_list[type->base_type]);
    else return false;
}

bool isTypeReal(Type *type) {
    if (type->base_type == TY_REAL) return true;
    else if (type->base_type >= TY_CUSTOM) return isTypeReal(type_list[type->base_type]);
    else return false;
}

bool isTypeChar(Type *type) {
    if (type->base_type == TY_CHAR) return true;
    else if (type->base_type >= TY_CUSTOM) return isTypeChar(type_list[type->base_type]);
    else return false;
}

bool isTypeRecord(Type *type) {
    if (type->base_type == TY_RECORD) return true;
    else if (type->base_type >= TY_CUSTOM) return isTypeRecord(type_list[type->base_type]);
    else return false;
}

bool isTypeArray(Type *type) {
    if (type->base_type == TY_ARRAY) return true;
    else if (type->base_type >= TY_CUSTOM) return isTypeArray(type_list[type->base_type]);
    else return false;
}

bool isTypeString(Type *type) {
    if (type->base_type == TY_STRING) return true;
    else if (type->base_type >= TY_CUSTOM) return isTypeString(type_list[type->base_type]);
    else return false;
}

Type *generateTypeByValue(Value *value) {
    Type *type;
    switch (value->base_type) {
        case TY_INTEGER:
        case TY_REAL:
        case TY_CHAR:
        case TY_BOOLEAN:
        case TY_STRING:
            type = new Type(value->base_type);
            break;
        case TY_RECORD:
            type = new Type(value->base_type);
            for (auto val: (*(value->val.children_value)))
                type->child_type.push_back(generateTypeByValue(val));
            break;
        case TY_ARRAY:
            type = new Type(TY_ARRAY);
            type->array_start = 0;
            type->array_end = (*(value->val.children_value)).size() - 1;
            type->child_type.push_back(generateTypeByValue((*(value->val.children_value))[0]));
            break;
        default:
            type = nullptr;
    }
    return type;
}

Type *findChildType(Type *pType, const std::string &basic_string) {
    if (pType->base_type != TY_RECORD) return nullptr;
    for (Type *child: pType->child_type)
        if (child->name == basic_string) return child;
    return nullptr;
}

bool canFindChild(Type *pType, const std::string &basic_string) {
    if (pType->base_type != TY_RECORD) return false;
    for (Type *child: pType->child_type)
        if (child->name == basic_string) return true;
    return false;
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
    if (is_legal)
        for (ConstDef *c_iter: const_def) {
            if (is_legal)
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
    if (is_legal)
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
    if (is_legal)
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
        for (std::string arg_name: args_name) {
            if (arg_name == name) {
                is_legal = false;
                break;
            }
            if (is_legal)
                for (ConstDef *iter: const_def)
                    if (iter->name == arg_name) {
                        is_legal = false;
                        break;
                    }
            if (is_legal)
                for (TypeDef *iter: type_def)
                    if (iter->name == arg_name) {
                        is_legal = false;
                        break;
                    }
            if (is_legal)
                for (VarDef *iter: var_def)
                    if (iter->name == arg_name) {
                        is_legal = false;
                        break;
                    }
            if (is_legal)
                for (FunctionDef *iter: function_def)
                    if (iter->name == arg_name) {
                        is_legal = false;
                        break;
                    }
        }
    }
    if (is_legal)
        for (ConstDef *iter: const_def)
            if (iter->name == name) {
                is_legal = false;
                break;
            }
    if (is_legal)
        for (TypeDef *iter: type_def)
            if (iter->name == name) {
                is_legal = false;
                break;
            }
    if (is_legal)
        for (VarDef *iter: var_def)
            if (iter->name == name) {
                is_legal = false;
                break;
            }
    if (is_legal)
        for (FunctionDef *iter: function_def)
            if (iter->name == name) {
                is_legal = false;
                break;
            }
    if (is_legal)
        is_legal = body->checkSemantics();
    // check between children
    // check itself
    return is_legal;
}

// stm
bool AssignStm::checkSemantics() {
    // check children
    is_legal = left_value->checkSemantics() && right_value->checkSemantics();
    // check between children
    if (is_legal) is_legal = isSameType(left_value->return_type, right_value->return_type);
    // check itself
    if (is_legal)
        if (left_value->return_value != nullptr)
            is_legal = false;
    return is_legal;
}

bool CallStm::checkSemantics() {
    // check children
    for (Exp *iter: args)
        is_legal &= iter->checkSemantics();
    // check between children
    // check itself
    FunctionDef *function = findFunction(name, this->father);
    if (function == nullptr) is_legal = false;
    else if (args.size() != function->args_type.size()) is_legal = false;
    else {
        for (int i = 0; i < args.size(); i++)
            if (!isSameType(args[i].return_type, function->args_type[i])) {
                is_legal = false;
                break;
            }
    }
    return is_legal;
}

bool CaseStm::checkSemantics() {
    // 全常量检测
    for (auto situation: situations)
        for (auto match_item: situation->match_list)
            if (match_item->return_value == nullptr) {
                char info[200];
                sprintf(info, "The match items in case statement must be constant.");
                yyerror(info);
                is_legal = false;
                return;
            }
    // 类型匹配
    bool is_int = isTypeInt(object->return_type);
    for (auto situation: situations)
        for (auto match_item: situation->match_list)
            if (is_int != isTypeInt(match_item->return_type)) {
                char info[200];
                sprintf(info, "The match items in case statement must have the same type as the switch object.");
                yyerror(info);
                is_legal = false;
                return;
            }
    // 重复值检测
    bool flag[65536];
    for (bool &i : flag) i = false;
    for (auto situation: situations)
        for (Exp *match_item: situation->match_list) {
            int id = is_int ? (match_item->return_value->val.integer_value + 32768)
                            : ((int) match_item->return_value->val.char_value);
            if (flag[id]) {
                char info[200];
                sprintf(info, "The match items in case statement must be different.");
                yyerror(info);
                is_legal = false;
                return;
            }
            flag[id] = true;
        }
    return is_legal;
}

bool ForStm::checkSemantics() {
    start->checkSemantics();
    end->checkSemantics();
    if ((isTypeInt(start->return_type) && isTypeInt(end->return_type)) ||
        (isTypeChar(start->return_type) && isTypeChar(end->return_type))) {
        char info[200];
        sprintf(info, "The start index or the end index is illegal.");
        yyerror(info);
        is_legal = false;
    }
    is_legal &= loop->checkSemantics();
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
    is_legal = operand->checkSemantics();
    if (is_legal)
        switch (op_code) {
            case OP_OPPO: {
                if (!isTypeInt(operand->return_type) && !isTypeReal(operand->return_type)) {
                    char info[200];
                    sprintf(info, "The type of an operand with an unary operator \'-\' must be integer or real.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = copyType(operand->return_type);
                }
            }
                break;
            case OP_NOT: {
                if (!isTypeChar(operand->return_type)) {
                    char info[200];
                    sprintf(info, "The type of an operand with an unary operator \'not\' must be boolean.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_BOOLEAN);
                }
            }
                break;
            case OP_ABS: {
                if (!isTypeInt(operand->return_type) && !isTypeReal(operand->return_type)) {
                    char info[200];
                    sprintf(info, "The type of the parameter in function \'abs\' must be integer or real.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = copyType(operand->return_type);
                }
            }
                break;
            case OP_PRED: {
                if (!isTypeChar(operand->return_type)) {
                    char info[200];
                    sprintf(info, "The type of the parameter in function \'pred\' must be char.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_CHAR);
                }
            }
                break;
            case OP_SUCC: {
                if (!isTypeChar(operand->return_type)) {
                    char info[200];
                    sprintf(info, "The type of the parameter in function \'succ\' must be char.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_CHAR);
                }
            }
                break;
            case OP_ODD: {
                if (!isTypeInt(operand->return_type)) {
                    char info[200];
                    sprintf(info, "The type of the parameter in function \'odd\' must be integer.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_BOOLEAN);
                }
            }
                break;
            case OP_CHR: {
                if (!isTypeInt(operand->return_type)) {
                    char info[200];
                    sprintf(info, "The type of the parameter in function \'chr\' must be integer.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_CHAR);
                }
            }
                break;
            case OP_ORD: {
                if (!isTypeChar(operand->return_type)) {
                    char info[200];
                    sprintf(info, "The type of the parameter in function \'ord\' must be char.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_INTEGER);
                }
            }
                break;
            case OP_SQR: {
                if (!isTypeInt(operand->return_type) && !isTypeReal(operand->return_type)) {
                    char info[200];
                    sprintf(info, "The type of the parameter in function \'sqr\' must be integer or real.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_REAL);
                }
            }
                break;
            case OP_SQRT: {
                if (!isTypeInt(operand->return_type) && !isTypeReal(operand->return_type)) {
                    char info[200];
                    sprintf(info, "The type of the parameter in function \'sqrt\' must be integer or real.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_REAL);
                }
            }
                break;
            default: {
                char info[200];
                sprintf(info, "There is something wrong. This operator type is unrecognised.");
                yyerror(info);
                is_legal = false;
            }
        }
    return is_legal;
}

bool BinaryExp::checkSemantics() {
    is_legal = operand1->checkSemantics();
    if (is_legal)
        switch (op_code) {
            case OP_ADD: {
                is_legal &= operand2->checkSemantics();
                if (!is_legal) return is_legal;
                if ((!isTypeInt(operand1->return_type) && !isTypeReal(operand1->return_type)) ||
                    (!isTypeInt(operand2->return_type) && !isTypeReal(operand2->return_type))) {
                    char info[200];
                    sprintf(info, "The type of operands with a binary operator \'+\' must be integer or real.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    if (isTypeReal(operand1->return_type) || isTypeReal(operand2->return_type))
                        return_type = new Type(TY_REAL);
                    else return_type = new Type(TY_INTEGER);
                }
            }
                break;
            case OP_MINUS: {
                is_legal &= operand2->checkSemantics();
                if (!is_legal) return is_legal;
                if ((!isTypeInt(operand1->return_type) && !isTypeReal(operand1->return_type)) ||
                    (!isTypeInt(operand2->return_type) && !isTypeReal(operand2->return_type))) {
                    char info[200];
                    sprintf(info, "The type of operands with a binary operator \'-\' must be integer or real.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    if (isTypeReal(operand1->return_type) || isTypeReal(operand2->return_type))
                        return_type = new Type(TY_REAL);
                    else return_type = new Type(TY_INTEGER);
                }
            }
                break;
            case OP_MULTI: {
                is_legal &= operand2->checkSemantics();
                if (!is_legal) return is_legal;
                if ((!isTypeInt(operand1->return_type) && !isTypeReal(operand1->return_type)) ||
                    (!isTypeInt(operand2->return_type) && !isTypeReal(operand2->return_type))) {
                    char info[200];
                    sprintf(info, "The type of operands with a binary operator \'*\' must be integer or real.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    if (isTypeReal(operand1->return_type) || isTypeReal(operand2->return_type))
                        return_type = new Type(TY_REAL);
                    else return_type = new Type(TY_INTEGER);
                }
            }
                break;
            case OP_RDIV: {
                is_legal &= operand2->checkSemantics();
                if (!is_legal) return is_legal;
                if ((!isTypeInt(operand1->return_type) && !isTypeReal(operand1->return_type)) ||
                    (!isTypeInt(operand2->return_type) && !isTypeReal(operand2->return_type))) {
                    char info[200];
                    sprintf(info, "The type of operands with a binary operator \'/\' must be integer or real.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_REAL);
                }
            }
                break;
            case OP_DDIV: {
                is_legal &= operand2->checkSemantics();
                if (!is_legal) return is_legal;
                if ((!isTypeInt(operand1->return_type) && !isTypeReal(operand1->return_type)) ||
                    (!isTypeInt(operand2->return_type) && !isTypeReal(operand2->return_type))) {
                    char info[200];
                    sprintf(info, "The type of operands with a binary operator \'div\' must be integer or real.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_INTEGER);
                }
            }
                break;
            case OP_MOD: {
                is_legal &= operand2->checkSemantics();
                if (!is_legal) return is_legal;
                if (!isTypeInt(operand1->return_type) || !isTypeInt(operand2->return_type)) {
                    char info[200];
                    sprintf(info, "The type of operands with a binary operator \'%%\' must be integer.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_INTEGER);
                }
            }
                break;
            case OP_AND: {
                is_legal &= operand2->checkSemantics();
                if (!is_legal) return is_legal;
                if (!isTypeChar(operand1->return_type) || !isTypeChar(operand2->return_type)) {
                    char info[200];
                    sprintf(info, "The type of operands with a binary operator \'and\' must be boolean.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_BOOLEAN);
                }
            }
                break;
            case OP_OR: {
                is_legal &= operand2->checkSemantics();
                if (!is_legal) return is_legal;
                if (!isTypeChar(operand1->return_type) || !isTypeChar(operand2->return_type)) {
                    char info[200];
                    sprintf(info, "The type of operands with a binary operator \'or\' must be boolean.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_BOOLEAN);
                }
            }
                break;
            case OP_SMALL: {
                is_legal &= operand2->checkSemantics();
                if (!is_legal) return is_legal;
                if ((!isTypeInt(operand1->return_type) && !isTypeReal(operand1->return_type) &&
                     !isTypeChar(operand1->return_type)) ||
                    (!isTypeInt(operand2->return_type) && !isTypeReal(operand2->return_type) &&
                     !isTypeChar(operand1->return_type))) {
                    char info[200];
                    sprintf(info, "The type of operands with a binary operator \'<\' must be integer, real or char.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_BOOLEAN);
                }
            }
                break;
            case OP_LARGE: {
                is_legal &= operand2->checkSemantics();
                if (!is_legal) return is_legal;
                if ((!isTypeInt(operand1->return_type) && !isTypeReal(operand1->return_type) &&
                     !isTypeChar(operand1->return_type)) ||
                    (!isTypeInt(operand2->return_type) && !isTypeReal(operand2->return_type) &&
                     !isTypeChar(operand1->return_type))) {
                    char info[200];
                    sprintf(info, "The type of operands with a binary operator \'>\' must be integer, real or char.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_BOOLEAN);
                }
            }
                break;
            case OP_SMALL_EQUAL: {
                is_legal &= operand2->checkSemantics();
                if (!is_legal) return is_legal;
                if ((!isTypeInt(operand1->return_type) && !isTypeReal(operand1->return_type) &&
                     !isTypeChar(operand1->return_type)) ||
                    (!isTypeInt(operand2->return_type) && !isTypeReal(operand2->return_type) &&
                     !isTypeChar(operand1->return_type))) {
                    char info[200];
                    sprintf(info, "The type of operands with a binary operator \'<=\' must be integer, real or char.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_BOOLEAN);
                }
            }
                break;
            case OP_LARGE_EQUAL: {
                is_legal &= operand2->checkSemantics();
                if (!is_legal) return is_legal;
                if ((!isTypeInt(operand1->return_type) && !isTypeReal(operand1->return_type) &&
                     !isTypeChar(operand1->return_type)) ||
                    (!isTypeInt(operand2->return_type) && !isTypeReal(operand2->return_type) &&
                     !isTypeChar(operand1->return_type))) {
                    char info[200];
                    sprintf(info, "The type of operands with a binary operator \'>=\' must be integer, real or char.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_BOOLEAN);
                }
            }
                break;
            case OP_EQUAL: {
                is_legal &= operand2->checkSemantics();
                if (!is_legal) return is_legal;
                if ((!isTypeInt(operand1->return_type) && !isTypeReal(operand1->return_type) &&
                     !isTypeChar(operand1->return_type)) ||
                    (!isTypeInt(operand2->return_type) && !isTypeReal(operand2->return_type) &&
                     !isTypeChar(operand1->return_type))) {
                    char info[200];
                    sprintf(info, "The type of operands with a binary operator \'=\' must be integer, real or char.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_BOOLEAN);
                }
            }
                break;
            case OP_NOT_EQUAL: {
                is_legal &= operand2->checkSemantics();
                if (!is_legal) return is_legal;
                if ((!isTypeInt(operand1->return_type) && !isTypeReal(operand1->return_type) &&
                     !isTypeChar(operand1->return_type)) ||
                    (!isTypeInt(operand2->return_type) && !isTypeReal(operand2->return_type) &&
                     !isTypeChar(operand1->return_type))) {
                    char info[200];
                    sprintf(info, "The type of operands with a binary operator \'<>\' must be integer, real or char.");
                    yyerror(info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_BOOLEAN);
                }
            }
                break;
            case OP_DOT: {
                if (isTypeRecord(operand1->return_type))
                    if (canFindChild(operand1->return_type, ((VariableExp *) operand2)->name))
                        return_type = copyType(findChildType(operand1->return_type, ((VariableExp *) operand2)->name));
                    else {
                        char info[200];
                        sprintf(info, "Cannot find child named %s in this record.", ((VariableExp *) operand2)->name);
                        yyerror(info);
                        is_legal = false;
                    }
                else {
                    char info[200];
                    sprintf(info, "The type of the first operand in the binary operator \'.\' must be record.");
                    yyerror(info);
                    is_legal = false;
                }
            }
                break;
            case OP_INDEX: {
                is_legal &= operand2->checkSemantics();
                if (!is_legal) return is_legal;
                if (isTypeArray(operand1->return_type) || isTypeString(operand1->return_type))
                    if (isTypeInt(operand2->return_type) || isTypeChar(operand2->return_type))
                        return_type = copyType(operand1->return_type->child_type[0]);
                    else {
                        char info[200];
                        sprintf(info, "The index must be integer or char.");
                        yyerror(info);
                        is_legal = false;
                    }
                else {
                    char info[200];
                    sprintf(info,
                            "The type of the first operand in the binary operator \'[]\' must be array or string.");
                    yyerror(info);
                    is_legal = false;
                }
            }
                break;
            default: {
                char info[200];
                sprintf(info, "There is something wrong. This operator type is unrecognised.");
                yyerror(info);
                is_legal = false;
            }
        }
    return is_legal;
}

bool CallExp::checkSemantics() {
    // check children
    for (Exp *iter: args)
        is_legal &= iter->checkSemantics();
    // check between children
    // check itself
    FunctionDef *function = findFunction(name, this->father);
    if (function == nullptr) is_legal = false;
    else if (args.size() != function->args_type.size()) is_legal = false;
    else {
        for (int i = 0; i < args.size(); i++)
            if (!isSameType(args[i].return_type, function->args_type[i])) {
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
    if (temp == nullptr) is_legal = false;
    else
        switch (temp->node_type) {
            case N_CONST_DEF: {
                ConstDef *node = (ConstDef *) temp;
                is_legal = true;
                return_type = node->value->return_type;
                return_value = node->value->return_value;
            }
                break;
            case N_VAR_DEF: {
                VarDef *node = (VarDef *) temp;
                is_legal = true;
                return_type = node->type;
            }
                break;
            case N_ARG_DEF: {
                ArgDef *node = (ArgDef *) temp;
                is_legal = true;
                return_type = node->type;
            }
                break;
            default:
                is_legal = false;
        }
    return is_legal;
}

#endif
