//
// Created by WuJiang on 2018/5/30.
//

#include "tree.h"
#include <fstream>

void yyerror(const char *info) {
    printf("%s\n", info);
}

bool canFillTypeWithValue(Type *type, Value *value) {
    switch (type->base_type) {
        case TY_REAL:
            return value->base_type == TY_INTEGER || value->base_type == TY_REAL;
        case TY_INTEGER: case TY_CHAR: case TY_BOOLEAN:
            return value->base_type == type->base_type;
        case TY_STRING:
            return value->base_type == TY_CHAR || value->base_type == TY_STRING;
        case TY_ARRAY:
            if (value->base_type != TY_ARRAY) return false;
            if (type->array_end - type->array_start + 1 != value->val->children_value.size()) return false;
            for (int i = 0; i <= type->array_end - type->array_start; i++)
                if (!canFillTypeWithValue(type->child_type[i], value->val->children_value[i])) return false;
            return true;
        case TY_RECORD:
            if (value->base_type != TY_RECORD) return false;
            if (type->child_type.size() != value->val->children_value.size()) return false;
            for (int i = 0; i < type->child_type.size(); i++)
                if (!canFillTypeWithValue(type->child_type[0], value->val->children_value[i])) return false;
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
        case TY_INTEGER: case TY_REAL: case TY_CHAR: case TY_BOOLEAN: case TY_STRING:
            type = new Type(value->base_type);
            break;
        case TY_SET: case TY_RECORD:
            type = new Type(value->base_type);
            for (auto val: value->val->children_value)
                type->child_type.push_back(generateTypeByValue(val));
            break;
        case TY_ARRAY:
            type = new Type(TY_ARRAY);
            type->array_start = 0;
            type->array_end = value->val->children_value.size() - 1;
            type->child_type.push_back(generateTypeByValue(value->val->children_value[0]));
            break;
        default:
            type = nullptr;
    }
    return type;
}

Type *copyType(Type *type) {
    Type *new_type;
    switch (type->base_type) {
        case TY_INTEGER: case TY_REAL: case TY_CHAR: case TY_BOOLEAN: case TY_STRING:
            return new Type(type->base_type);
        case TY_SET: case TY_RECORD:
            new_type = new Type(type->base_type);
            for (auto child: type->child_type)
                new_type->child_type.push_back(copyType(child));
            return new_type;
        case TY_ARRAY:
            new_type = new Type(TY_ARRAY);
            new_type->array_start = type->array_start;
            new_type->array_end = type->array_end;
            new_type->child_type.push_back(copyType(type->child_type[0]));
            return new_type;
        default:
            return new Type(type->base_type);
    }
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

Base::Base(int type) {
    this->node_type = type;
}

Stm::Stm(int type) : Base(type) {}

Exp::Exp(int type) : Base(type) {}

Program::Program(const std::string &name) : Base(N_PROGRAM) {
    this->name = name;
}

void Program::addDefine(Define *define) {
    if (this->define == nullptr) this->define = define;
}

Define::Define() : Base(N_DEFINE) {
    label_def.clear();
    const_def.clear();
    type_def.clear();
    var_def.clear();
    function_def.clear();
}

void Define::addLabel(LabelDef *def) {
    bool is_defined = false;
    for (auto label: label_def)
        if (def->label_index == label->label_index) {
            is_defined = true;
            break;
        }
    if (is_defined) {
        char info[200];
        sprintf(info, "There are two label %d.", def->label_index);
        yyerror(info);
        is_legal = false;
    } else label_def.push_back(def);
}

void Define::addConst(ConstDef *def) {
    bool is_defined = false;
    for (auto const_iter: const_def)
        if (def->name == const_iter->name) {
            is_defined = true;
            break;
        }
    if (!is_defined)
        for (auto type_iter: type_def)
            if (def->name == type_iter->name) {
                is_defined = true;
                break;
            }
    if (!is_defined)
        for (auto var_iter: var_def)
            if (def->name == var_iter->name) {
                is_defined = true;
                break;
            }
    if (!is_defined)
        for (auto func_iter: function_def)
            if (def->name == func_iter->name) {
                is_defined = true;
                break;
            }
    if (is_defined) {
        char info[200];
        sprintf(info, "There are two const, type, variable, function or procedure has the same name %s.", def->name);
        yyerror(info);
        is_legal = false;
    } else const_def.push_back(def);
}

void Define::addType(TypeDef *def) {
    bool is_defined = false;
    for (auto const_iter: const_def)
        if (def->name == const_iter->name) {
            is_defined = true;
            break;
        }
    if (!is_defined)
        for (auto type_iter: type_def)
            if (def->name == type_iter->name) {
                is_defined = true;
                break;
            }
    if (!is_defined)
        for (auto var_iter: var_def)
            if (def->name == var_iter->name) {
                is_defined = true;
                break;
            }
    if (!is_defined)
        for (auto func_iter: function_def)
            if (def->name == func_iter->name) {
                is_defined = true;
                break;
            }
    if (is_defined) {
        char info[200];
        sprintf(info, "There are two const, type, variable, function or procedure has the same name %s.", def->name);
        yyerror(info);
        is_legal = false;
    } else type_def.push_back(def);
}

void Define::addVar(VarDef *def) {
    bool is_defined = false;
    for (auto const_iter: const_def)
        if (def->name == const_iter->name) {
            is_defined = true;
            break;
        }
    if (!is_defined)
        for (auto type_iter: type_def)
            if (def->name == type_iter->name) {
                is_defined = true;
                break;
            }
    if (!is_defined)
        for (auto var_iter: var_def)
            if (def->name == var_iter->name) {
                is_defined = true;
                break;
            }
    if (!is_defined)
        for (auto func_iter: function_def)
            if (def->name == func_iter->name) {
                is_defined = true;
                break;
            }
    if (is_defined) {
        char info[200];
        sprintf(info, "There are two const, type, variable, function or procedure has the same name %s.", def->name);
        yyerror(info);
        is_legal = false;
    } else var_def.push_back(def);
}

void Define::addFunction(FunctionDef *def) {
    bool is_defined = false;
    for (auto const_iter: const_def)
        if (def->name == const_iter->name) {
            is_defined = true;
            break;
        }
    if (!is_defined)
        for (auto type_iter: type_def)
            if (def->name == type_iter->name) {
                is_defined = true;
                break;
            }
    if (!is_defined)
        for (auto var_iter: var_def)
            if (def->name == var_iter->name) {
                is_defined = true;
                break;
            }
    if (!is_defined)
        for (auto func_iter: function_def)
            if (def->name == func_iter->name) {
                is_defined = true;
                break;
            }
    if (is_defined) {
        char info[200];
        sprintf(info, "There are two const, type, variable, function or procedure has the same name %s.", def->name);
        yyerror(info);
        is_legal = false;
    } else function_def.push_back(def);
}

Body::Body() : Base(N_BODY) {
    stms.clear();
}

void Body::addStm(Stm *stm) {
    stms.push_back(stm);
}

Situation::Situation() : Base(N_SITUATION) {
    match_list.clear();
}

void Situation::addMatch(Exp *exp) {
    match_list.push_back(exp);
}

LabelDef::LabelDef(int index) : Base(N_LABEL_DEF) {
    label_index = index;
}

ConstDef::ConstDef(const std::string &name, Exp *val) : Base(N_CONST_DEF) {
    this->name = name;
    this->value = val;
}

TypeDef::TypeDef(const std::string &name, Type *type) : Base(N_TYPE_DEF) {
    this->name = name;
    this->type = type;
}

VarDef::VarDef(const std::string &name, Type *type) : Base(N_VAR_DEF) {
    this->name = name;
    this->type = type;
}

FunctionDef::FunctionDef(const std::string &name) : Base(N_FUNCTION_DEF) {
    this->name = name;
    args_type.clear();
    args_name.clear();
}

void FunctionDef::addArgs(const std::string &arg_name, Type *arg_type, bool is_formal_parameter) {
    bool is_defined = false;
    for (auto arg_iter: args_name)
        if (arg_name == arg_iter) {
            is_defined = true;
            break;
        }
    if (is_defined) {
        char info[300];
        sprintf(info, "There are two arguments has the same name %s, in function %s.", arg_name, name);
        yyerror(info);
        is_legal = false;
    } else {
        args_name.push_back(arg_name);
        args_type.push_back(arg_type);
        args_is_formal_parameters.push_back(is_formal_parameter);
    }
}

void FunctionDef::setReturnType(Type *rtn_type) {
    if (this->rtn_type == nullptr) this->rtn_type = rtn_type;
}

void FunctionDef::addDefine(Define *def) {
    if (define == nullptr) define = def;
    // define 和 arguments 重复性判定，暂时不管
}

AssignStm::AssignStm(const std::string &left, Exp *right) : Stm(N_ASSIGN_STM) {
    this->left_value = left;
    this->right_value = right;
}

WithStm::WithStm(const std::string &name) : Stm(N_WITH_STM) {
    this->name = name;
    // body 内 可以省去此前缀，样例里没有，暂时不管
}

CallStm::CallStm(const std::string &name) : Stm(N_CALL_STM) {
    this->name = name;
    args.clear();
}

void CallStm::addArgs(Exp *exp) {
    this->args.push_back(exp);
}

LabelStm::LabelStm(const int &label) : Stm(N_LABEL_STM) {
    this->label = label;
    // 重复性检测，避免跳转时出现多个目的地，暂时不管
}

IfStm::IfStm() : Stm(N_IF_STM) {}

void IfStm::setCondition(Exp *cond) {
    condition = cond;
}

void IfStm::addFalse() {
    this->false_do = new Body();
}

void IfStm::check() {
    if (!isTypeBoolean(condition->return_type)) {
        char info[200];
        sprintf(info, "There is a return value of the expression in if_cond, whose type is not boolean.");
        yyerror(info);
        is_legal = false;
    }
}

CaseStm::CaseStm(Exp *obj) : Stm(N_CASE_STM) {
    if (isTypeInt(obj->return_type) || isTypeChar(obj->return_type)) {
        object = obj;
        situations.clear();
    } else {
        char info[200];
        sprintf(info, "The type for case statement must be integer or char.");
        yyerror(info);
        is_legal = false;
    }
}

void CaseStm::addSituation(Situation *situation) {
    situations.push_back(situation);
    // 各个match情况的重复性检测，避免多入口，暂时不管
}

void CaseStm::check() {
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
        for (Exp* match_item: situation->match_list) {
            int id = is_int ? (match_item->return_value->val->integer_value + 32768) : ((int)match_item->return_value->val->char_value);
            if (flag[id]) {
                char info[200];
                sprintf(info, "The match items in case statement must be different.");
                yyerror(info);
                is_legal = false;
                return;
            }
            flag[id] = true;
        }
}

ForStm::ForStm(const std::string &iter, Exp *start, Exp *end, int step) : Stm(N_FOR_STM) {
    this->iter = iter;
    this->start = start;
    this->end = end;
    this->step = step;
}

void ForStm::check() {
    if ((isTypeInt(start->return_type) && isTypeInt(end->return_type)) ||
        (isTypeChar(start->return_type) && isTypeChar(end->return_type))) {
        char info[200];
        sprintf(info, "The start index and the end index is illegal.");
        yyerror(info);
        is_legal = false;
    }
}

WhileStm::WhileStm(Exp *cond) : Stm(N_WHILE_STM) {
    condition = cond;
}

void WhileStm::check() {
    if (!isTypeBoolean(condition->return_type)) {
        char info[200];
        sprintf(info, "There is a return value of the expression in while_cond, whose type is not boolean.");
        yyerror(info);
        is_legal = false;
    }
}

RepeatStm::RepeatStm() : Stm(N_REPEAT_STM) {}

void RepeatStm::setCondition(Exp *cond) {
    if (condition == nullptr) condition = cond;
}

void RepeatStm::check() {
    if (!isTypeBoolean(condition->return_type)) {
        char info[200];
        sprintf(info, "There is a return value of the expression in repeat_cond, whose type is not boolean.");
        yyerror(info);
        is_legal = false;
    }
}

GotoStm::GotoStm(int label) : Stm(label) {
    this->label = label;
}

UnaryExp::UnaryExp(int op_code, Exp *oprand) {
    this->op_code = op_code;
    this->operand = oprand;
}

void UnaryExp::check() {
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
}

BinaryExp::BinaryExp(int op_code, Exp *operand1, Exp *operand2) : Exp(N_BINARY_EXP) {
    this->op_code = op_code;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

void BinaryExp::check() {
    switch (op_code) {
        case OP_ADD: {
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
                sprintf(info, "The type of the first operand in the binary operator \'[]\' must be array or string.");
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
}

CallExp::CallExp(const std::string &name) : Exp(N_CALL_STM) {
    this->name = name;
    args.clear();
}

void CallExp::addArgs(Exp *exp) {
    args.push_back(exp);
}

ConstantExp::ConstantExp(Value *val) : Exp(N_CONSTANT_EXP) {
    return_value = value = val;
    return_type = generateTypeByValue(val);
}

VariableExp::VariableExp(const std::string &name) : Exp(N_VARIABLE_EXP) {
    this->name = name;
}

MemoryExp::MemoryExp(ADDRESS addr) : Exp(N_MEMORY_EXP) {
    address = addr;
}

Type::Type() : Base(N_TYPE) {}

Type::Type(int type_code) : Base(N_TYPE) {
    base_type = type_code;
}

std::string getString(Value *value) {
    std::string str;
    if (value == nullptr) str = "NULL";
    else
        switch (value->base_type) {
            case TY_INTEGER: {
                char val[10];
                sprintf(val, "%d", value->val->integer_value);
                str.append(val);
            }
                break;
            case TY_REAL: {
                char val[10];
                sprintf(val, "%.2f", value->val->real_value);
                str.append(val);
            }
                break;
            case TY_CHAR: {
                str.append("\'");
                char val[2];
                sprintf(val, "%c", value->val->char_value);
                str.append(val);
                str.append("\'");
            }
                break;
            case TY_BOOLEAN: {
                str.append(value->val->boolean_value ? "true" : "false");
            }
                break;
            case TY_SET:
            case TY_ARRAY:
            case TY_RECORD: {
                str.append("[");
                for (auto child: value->val->children_value) {
                    str.append(getString(child));
                    str.append(",");
                }
                str.append("]");
            }
            default: {
                str.append("\"There is something wrong. The type is unrecognised.\"");
            }
        }
    return str;
}

std::string getString(Base *ori_node) {
    std::string str;
    if (ori_node == nullptr) str = "NULL";
    else
        switch (ori_node->node_type) {
            case N_PROGRAM: {
                auto *node = (Program *) ori_node;
                str.append("{");
                str.append("name:\"");
                str.append(node->name);
                str.append("\",");
                str.append("define:");
                str.append(getString(node->define));
                str.append(",");
                str.append("body:");
                str.append(getString(node->body));
                str.append(",}");
            }
                break;
            case N_DEFINE: {
                auto *node = (Define *) ori_node;
                str.append("{");
                str.append("label: [");
                for (auto stm: node->label_def) {
                    str.append(getString(stm));
                    str.append(",");
                }
                str.append("],");
                str.append("const: [");
                for (auto stm: node->const_def) {
                    str.append(getString(stm));
                    str.append(",");
                }
                str.append("],");
                str.append("type: [");
                for (auto stm: node->type_def) {
                    str.append(getString(stm));
                    str.append(",");
                }
                str.append("],");
                str.append("var: [");
                for (auto stm: node->var_def) {
                    str.append(getString(stm));
                    str.append(",");
                }
                str.append("],");
                str.append("function: [");
                for (auto stm: node->function_def) {
                    str.append(getString(stm));
                    str.append(",");
                }
                str.append("],");
                str.append("}");
            }
                break;
            case N_BODY: {
                auto *node = (Body *) ori_node;
                str.append("[");
                for (auto stm: node->stms) {
                    str.append(getString(stm));
                    str.append(",");
                }
                str.append("]");
            }
                break;
            case N_SITUATION: {
                auto *node = (Situation *) ori_node;
                str.append("{match_list:[");
                for (auto match_item: node->match_list) {
                    str.append(getString(match_item));
                    str.append(",");
                }
                str.append("], to_do:");
                str.append(getString(node->solution));
                str.append("}");
            }
                break;
            case N_LABEL_DEF: {
                auto *node = (LabelDef *) ori_node;
                str.append("{label_def: ");
                char id[100];
                sprintf(id, "%d", node->label_index);
                str.append(id);
                str.append("}");
            }
                break;
            case N_CONST_DEF: {
                auto *node = (ConstDef *) ori_node;
                str.append("{const_name: \"");
                str.append(node->name);
                str.append("\", const_value: ");
                str.append(getString(node->value));
                str.append("}");
            }
                break;
            case N_TYPE_DEF: {
                auto *node = (TypeDef *) ori_node;
                str.append("{type_name: \"");
                str.append(node->name);
                str.append("\", structure: ");
                str.append(getString(node->type));
                str.append("}");
            }
                break;
            case N_VAR_DEF: {
                auto *node = (VarDef *) ori_node;
                str.append("{var_name: \"");
                str.append(node->name);
                str.append("\", structure: ");
                str.append(getString(node->type));
                str.append("}");
            }
                break;
            case N_FUNCTION_DEF: {
                auto *node = (FunctionDef *) ori_node;
                str.append("{func_name: \"");
                str.append(node->name);
                str.append("\", args: [");
                for (int i = 0; i < node->args_name.size(); i++) {
                    str.append("{arg_name:\"");
                    str.append(node->args_name[i]);
                    str.append("\", arg_type:");
                    str.append(getString(node->args_type[i]));
                    str.append("\", arg_is_formal_parameter:");
                    str.append(node->args_is_formal_parameters[i] ? "true" : "false");
                    str.append("},");
                }
                str.append("]");
                if (node->rtn_type != nullptr) {
                    str.append(", return_type: ");
                    str.append(getString(node->rtn_type));
                }
                if (node->define != nullptr) {
                    str.append(", defines: ");
                    str.append(getString(node->define));
                }
                str.append(", body: ");
                str.append(getString(node->body));
                str.append("}");
            }
                break;
            case N_ASSIGN_STM: {
                auto *node = (AssignStm *) ori_node;
                str.append("{left:\"");
                str.append(node->left_value);
                str.append("\",right:");
                str.append(getString(node->right_value));
                str.append("}");
            }
                break;
            case N_CALL_STM: {
                auto *node = (CallStm *) ori_node;
                str.append("{func:\"");
                str.append(node->name);
                str.append("\",args:[");
                for (auto arg: node->args) {
                    str.append(getString(arg));
                    str.append(",");
                }
                str.append("]}");
            }
                break;
            case N_CASE_STM: {
                auto *node = (CaseStm *) ori_node;
                str.append("{switch_item:\"");
                str.append(getString(node->object));
                str.append("\",situations:[");
                for (auto situation: node->situations) {
                    str.append(getString(situation));
                    str.append(",");
                }
                str.append("]}");
            }
                break;
            case N_FOR_STM: {
                auto *node = (ForStm *) ori_node;
                str.append("{iter:\"");
                str.append(node->iter);
                str.append("\",start:");
                str.append(getString(node->start));
                str.append(",end:");
                str.append(getString(node->end));
                str.append(",step:");
                if (node->step == 1) str.append("1");
                else str.append("-1");
                str.append(",body:");
                str.append(getString(node->loop));
                str.append("]}");
            }
                break;
            case N_GOTO_STM: {
                auto *node = (GotoStm *) ori_node;
                str.append("{goto:");
                char label[100];
                sprintf(label, "%d", node->label);
                str.append(label);
                str.append("}");
            }
                break;
            case N_IF_STM: {
                auto *node = (IfStm *) ori_node;
                str.append("{condition:");
                str.append(getString(node->condition));
                str.append(",true_body:");
                str.append(getString(node->true_do));
                if (node->false_do != nullptr) {
                    str.append(",false_body:");
                    str.append(getString(node->false_do));
                }
                str.append("}");
            }
                break;
            case N_LABEL_STM: {
                auto *node = (LabelStm *) ori_node;
                str.append("{label: ");
                char id[100];
                sprintf(id, "%d", node->label);
                str.append(id);
                str.append("}");
            }
                break;
            case N_REPEAT_STM: {
                auto *node = (RepeatStm *) ori_node;
                str.append("{body:");
                str.append(getString(node->loop));
                str.append(",condition:");
                str.append(getString(node->condition));
                str.append("}");
            }
                break;
            case N_WHILE_STM: {
                auto *node = (WhileStm *) ori_node;
                str.append("{condition:");
                str.append(getString(node->condition));
                str.append(",body:");
                str.append(getString(node->loop));
                str.append("}");
            }
                break;
            case N_WITH_STM: {
                auto *node = (WithStm *) ori_node;
                str.append("{with_var:\"");
                str.append(node->name);
                str.append("\",body:");
                str.append(getString(node->body));
                str.append("}");
            }
                break;
            case N_BINARY_EXP: {
                auto *node = (BinaryExp *) ori_node;
                str.append("{bin_op:\"");
                str.append(getOpNameByID(node->op_code));
                str.append("\",operand1:");
                str.append(getString(node->operand1));
                str.append("\",operand2:");
                str.append(getString(node->operand2));
                str.append("}");
            }
                break;
            case N_CALL_EXP: {
                auto *node = (CallExp *) ori_node;
                str.append("{func:\"");
                str.append(node->name);
                str.append("\",args:[");
                for (auto arg: node->args) {
                    str.append(getString(arg));
                    str.append(",");
                }
                str.append("]}");
            }
                break;
            case N_CONSTANT_EXP: {
                auto *node = (ConstantExp *) ori_node;
                str.append("{const_value:");
                str.append(getString(node->value));
                str.append("}");
            }
                break;
            case N_MEMORY_EXP: {
                auto *node = (MemoryExp *) ori_node;
                str.append("{mem_addr:");
                char hex_addr[100];
                sprintf(hex_addr, "%lx", node->address);
                str.append("\"}");
            }
                break;
            case N_UNARY_EXP: {
                auto *node = (UnaryExp *) ori_node;
                str.append("{mon_op:\"");
                str.append(getOpNameByID(node->op_code));
                str.append("\",operand:");
                str.append(getString(node->operand));
                str.append("}");
            }
                break;
            case N_VARIABLE_EXP: {
                auto *node = (VariableExp *) ori_node;
                str.append("{var_name:\"");
                str.append(node->name);
                str.append("\"}");
            }
                break;
            case N_TYPE: {
                auto *node = (Type *) ori_node;
                switch (node->base_type) {
                    case TY_INTEGER: {
                        str.append("\"integer\"");
                    }
                        break;
                    case TY_REAL: {
                        str.append("\"real\"");
                    }
                        break;
                    case TY_CHAR: {
                        str.append("\"char\"");
                    }
                        break;
                    case TY_BOOLEAN: {
                        str.append("\"boolean\"");
                    }
                        break;
                    case TY_SET: {
                        str.append("\"set\"");
                    }
                        break;
                    case TY_ARRAY: {
                        str.append("{type:\"array\",start_index:");
                        char num[100];
                        sprintf(num, "%d", node->array_start);
                        str.append(num);
                        str.append(",end_index:");
                        sprintf(num, "%d", node->array_end);
                        str.append(num);
                        str.append(",child_type:");
                        str.append(getString(node->child_type[0]));
                        str.append("}");
                    }
                        break;
                    case TY_RECORD: {
                        str.append("{type:\"record\",child_type:[");
                        for (auto child: node->child_type) {
                            str.append("{name:\"");
                            str.append(child->name);
                            str.append("\", type:");
                            str.append(getString(child));
                            str.append("},");
                            str.append("]}");
                        }
                    }
                        break;
                    default: {
                        if (node->base_type < type_list.size()) str.append(type_list[node->base_type]->name);
                        else str.append("\"There is something wrong. The type cannot be recognised.\"");
                    }
                }
            }
                break;
            default: {
                str.append("\"There is something wrong. The node is unrecognised.\"");
            }
        }
    return str;
}

void printTree(std::string filename, Base *root) {
    std::string str = getString(root);
    std::ofstream SaveFile(filename + ".json");
    SaveFile << str;
    SaveFile.close();
}
