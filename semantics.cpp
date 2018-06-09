//
// Created by WuJiang on 2018/6/8.
//

#include "tree.h"
#include "common.h"
#ifdef CHECK_SEMANTICS
#define DEBUG_MODE

using namespace ast;

void yyerror(Base *err_node, const char *info) {
    fprintf(stderr, "%p: %s\n", err_node, info);
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
            return false;
    }
}

bool isTypeBoolean(Type *type) {
    return type->base_type == TY_BOOLEAN;
}

bool isTypeInt(Type *type) {
    return type->base_type == TY_INTEGER;
}

bool isTypeReal(Type *type) {
    return type->base_type == TY_REAL;
}

bool isTypeChar(Type *type) {
    return type->base_type == TY_CHAR;
}

bool isTypeRecord(Type *type) {
    return type->base_type == TY_RECORD;
}

bool isTypeArray(Type *type) {
    return type->base_type == TY_ARRAY;
}

bool isTypeString(Type *type) {
    return type->base_type == TY_STRING;
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
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    // check children
    is_legal &= define->checkSemantics();
    if (is_legal) is_legal &= body->checkSemantics();
    // check between children
    // check itself
    return is_legal;
}

bool Define::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
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
                    if (v_iter->name == f_iter->name) {
                        is_legal = false;
                        break;
                    } else;
            else break;
        }
    if (!is_legal) {
        char info[200];
        sprintf(info, "Semantics Error: There are at least two obeject in define part, which has the same name.");
        yyerror(this, info);
    }
    // check itself
    return is_legal;
}

bool Body::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    // check children
    for (Stm *iter: stms)
        is_legal &= iter->checkSemantics();
    // check between children
    // check itself
    return is_legal;
}

bool Situation::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
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
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    // check children
    // check between children
    // check itself
    is_legal = true;
    return is_legal;
}

bool ConstDef::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    // check children
    // check between children
    // check itself
    is_legal = true;
    return is_legal;
}

bool TypeDef::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    // check children
    // check between children
    // check itself
    is_legal = true;
    return is_legal;
}

bool VarDef::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    // check children
    // check between children
    // check itself
    is_legal = true;
    return is_legal;
}

bool FunctionDef::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    // check children
    is_legal &= define->checkSemantics();
    if (is_legal) {
        for (std::string arg_name: args_name) {
            if (arg_name == name) {
                is_legal = false;
                break;
            }
            if (is_legal)
                for (ConstDef *iter: define->const_def)
                    if (iter->name == arg_name) {
                        is_legal = false;
                        break;
                    }
            if (is_legal)
                for (TypeDef *iter: define->type_def)
                    if (iter->name == arg_name) {
                        is_legal = false;
                        break;
                    }
            if (is_legal)
                for (VarDef *iter: define->var_def)
                    if (iter->name == arg_name) {
                        is_legal = false;
                        break;
                    }
            if (is_legal)
                for (FunctionDef *iter: define->function_def)
                    if (iter->name == arg_name) {
                        is_legal = false;
                        break;
                    }
        }
    }
    if (is_legal)
        for (ConstDef *iter: define->const_def)
            if (iter->name == name) {
                is_legal = false;
                break;
            }
    if (is_legal)
        for (TypeDef *iter: define->type_def)
            if (iter->name == name) {
                is_legal = false;
                break;
            }
    if (is_legal)
        for (VarDef *iter: define->var_def)
            if (iter->name == name) {
                is_legal = false;
                break;
            }
    if (is_legal)
        for (FunctionDef *iter: define->function_def)
            if (iter->name == name) {
                is_legal = false;
                break;
            }
    if (is_legal)
        is_legal = body->checkSemantics();
    else {  
        char info[200];
        sprintf(info, "Semantics Error: There are at least two obeject in function %s, which has the same name.", name.c_str());
        yyerror(this, info);
    }
    // check between children
    // check itself
    return is_legal;
}

// stm
bool AssignStm::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    // check children
    is_legal = left_value->checkSemantics() && right_value->checkSemantics();
    // check between children
    if (is_legal) is_legal = isSameType(left_value->return_type, right_value->return_type);
    // check itself
    if (is_legal)
        if (left_value->return_value != nullptr) {
            is_legal = false;
            char info[200];
            sprintf(info, "Semantics Error: Constant obeject cannot be the left value in an assignment statement.");
            yyerror(this, info);
        }
        else;
    else {
        char info[200];
        sprintf(info, "Semantics Error: Left value and right value must be the same type in an assignment statement.");
        yyerror(this, info);
    }
    return is_legal;
}

bool CallStm::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    // check children
    for (Exp *iter: args)
        is_legal &= iter->checkSemantics();
    // check between children
    // check itself
    if (name == "write" || name == "writeln") {
        is_legal = true;
    }
    else {
        FunctionDef *function = findFunction(name, this->father);
        if (function == nullptr) {
            is_legal = false;
            char info[200];
            sprintf(info, "Semantics Error: Cannot find function %s to call.", name.c_str());
            yyerror(this, info);
        }
        else if (args.size() != function->args_type.size()) {
            is_legal = false;
            char info[200];
            sprintf(info, "Semantics Error: The number of arguments are different between call and definition of function %s.", name.c_str());
            yyerror(this, info);
        }
        else {
            for (int i = 0; i < args.size(); i++)
                if (!isSameType(args[i]->return_type, function->args_type[i])) {
                    is_legal = false;
                    char info[200];
                    sprintf(info, "Semantics Error: No.%d argument has the differenct type between call and definition of function %s.", i, name.c_str());
                    yyerror(this, info);
                    break;
                }
        }
    }
    return is_legal;
}

bool CaseStm::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    // 全常量检测
    for (auto situation: situations)
        for (auto match_item: situation->match_list)
            if (match_item->return_value == nullptr) {
                char info[200];
                sprintf(info, "Semantics Error: The match items in case statement must be constant.");
                yyerror(this, info);
                is_legal = false;
                return is_legal;
            }
    // 类型匹配
    bool is_int = isTypeInt(object->return_type);
    for (auto situation: situations)
        for (auto match_item: situation->match_list)
            if (is_int != isTypeInt(match_item->return_type)) {
                char info[200];
                sprintf(info, "Semantics Error: The match items in case statement must have the same type as the switch object.");
                yyerror(this, info);
                is_legal = false;
                return is_legal;
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
                sprintf(info, "Semantics Error: The match items in case statement must be different.");
                yyerror(this, info);
                is_legal = false;
                return is_legal;
            }
            flag[id] = true;
        }
    return is_legal;
}

bool ForStm::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    start->checkSemantics();
    end->checkSemantics();
    if ((isTypeInt(start->return_type) && isTypeInt(end->return_type)) ||
        (isTypeChar(start->return_type) && isTypeChar(end->return_type))) {
        char info[200];
        sprintf(info, "Semantics Error: The start index or the end index is illegal.");
        yyerror(this, info);
        is_legal = false;
    }
    is_legal &= loop->checkSemantics();
    return is_legal;
}

bool GotoStm::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    // check children
    // check between children
    // check itself
    is_legal &= canFindLabel(label, this->father);
    if (!is_legal) {
        char info[200];
        sprintf(info, "Semantics Error: Cannot find label %d.", label);
        yyerror(this, info);
    }
    return is_legal;
}

bool IfStm::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    // check children
    is_legal &= condition->checkSemantics();
    is_legal &= true_do->checkSemantics();
    if (false_do != nullptr) is_legal &= false_do->checkSemantics();
    // check between children
    // check itself
    if (isTypeBoolean(condition->return_type))
        is_legal &= true;
    else {
        char info[200];
        sprintf(info, "Semantics Error: The type for the condition must be boolean.");
        yyerror(this, info);
        is_legal = false;
    }
    return is_legal;
}

bool LabelStm::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    // check children
    // check between children
    // check itself
    is_legal &= canFindLabel(label, this->father);
    if (!is_legal) {
        char info[200];
        sprintf(info, "Semantics Error: Cannot find label %d.", label);
        yyerror(this, info);
    }
    return is_legal;
}

bool RepeatStm::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    // check children
    is_legal &= condition->checkSemantics();
    is_legal &= loop->checkSemantics();
    // check between children
    // check itself
    if (isTypeBoolean(condition->return_type))
        is_legal &= true;
    else {
        char info[200];
        sprintf(info, "Semantics Error: The type for the condition must be boolean.");
        yyerror(this, info);
        is_legal = false;
    }
    return is_legal;
}

bool WhileStm::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    // check children
    is_legal &= condition->checkSemantics();
    is_legal &= loop->checkSemantics();
    // check between children
    // check itself
    if (isTypeBoolean(condition->return_type))
        is_legal &= true;
    else {
        char info[200];
        sprintf(info, "Semantics Error: The type for the condition must be boolean.");
        yyerror(this, info);
        is_legal = false;
    }
    return is_legal;
}

// exp
bool UnaryExp::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    is_legal = operand->checkSemantics();
    if (is_legal)
        switch (op_code) {
            case OP_OPPO: {
                if (!isTypeInt(operand->return_type) && !isTypeReal(operand->return_type)) {
                    char info[200];
                    sprintf(info, "Semantics Error: The type of an operand with an unary operator \'-\' must be integer or real.");
                    yyerror(this, info);
                    is_legal = false;
                } else {
                    return_type = copyType(operand->return_type);
                }
            }
                break;
            case OP_NOT: {
                if (!isTypeChar(operand->return_type)) {
                    char info[200];
                    sprintf(info, "Semantics Error: The type of an operand with an unary operator \'not\' must be boolean.");
                    yyerror(this, info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_BOOLEAN);
                }
            }
                break;
            case OP_ABS: {
                if (!isTypeInt(operand->return_type) && !isTypeReal(operand->return_type)) {
                    char info[200];
                    sprintf(info, "Semantics Error: The type of the parameter in function \'abs\' must be integer or real.");
                    yyerror(this, info);
                    is_legal = false;
                } else {
                    return_type = copyType(operand->return_type);
                }
            }
                break;
            case OP_PRED: {
                if (!isTypeChar(operand->return_type)) {
                    char info[200];
                    sprintf(info, "Semantics Error: The type of the parameter in function \'pred\' must be char.");
                    yyerror(this, info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_CHAR);
                }
            }
                break;
            case OP_SUCC: {
                if (!isTypeChar(operand->return_type)) {
                    char info[200];
                    sprintf(info, "Semantics Error: The type of the parameter in function \'succ\' must be char.");
                    yyerror(this, info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_CHAR);
                }
            }
                break;
            case OP_ODD: {
                if (!isTypeInt(operand->return_type)) {
                    char info[200];
                    sprintf(info, "Semantics Error: The type of the parameter in function \'odd\' must be integer.");
                    yyerror(this, info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_BOOLEAN);
                }
            }
                break;
            case OP_CHR: {
                if (!isTypeInt(operand->return_type)) {
                    char info[200];
                    sprintf(info, "Semantics Error: The type of the parameter in function \'chr\' must be integer.");
                    yyerror(this, info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_CHAR);
                }
            }
                break;
            case OP_ORD: {
                if (!isTypeChar(operand->return_type)) {
                    char info[200];
                    sprintf(info, "Semantics Error: The type of the parameter in function \'ord\' must be char.");
                    yyerror(this, info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_INTEGER);
                }
            }
                break;
            case OP_SQR: {
                if (!isTypeInt(operand->return_type) && !isTypeReal(operand->return_type)) {
                    char info[200];
                    sprintf(info, "Semantics Error: The type of the parameter in function \'sqr\' must be integer or real.");
                    yyerror(this, info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_REAL);
                }
            }
                break;
            case OP_SQRT: {
                if (!isTypeInt(operand->return_type) && !isTypeReal(operand->return_type)) {
                    char info[200];
                    sprintf(info, "Semantics Error: The type of the parameter in function \'sqrt\' must be integer or real.");
                    yyerror(this, info);
                    is_legal = false;
                } else {
                    return_type = new Type(TY_REAL);
                }
            }
                break;
            default: {
                char info[200];
                sprintf(info, "Semantics Error: There is something wrong. This operator type is unrecognised.");
                yyerror(this, info);
                is_legal = false;
            }
        }
    return is_legal;
}

bool BinaryExp::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    is_legal = operand1->checkSemantics();
    if (is_legal)
        switch (op_code) {
            case OP_ADD: {
                is_legal &= operand2->checkSemantics();
                if (!is_legal) return is_legal;
                if ((!isTypeInt(operand1->return_type) && !isTypeReal(operand1->return_type)) ||
                    (!isTypeInt(operand2->return_type) && !isTypeReal(operand2->return_type))) {
                    char info[200];
                    sprintf(info, "Semantics Error: The type of operands with a binary operator \'+\' must be integer or real.");
                    yyerror(this, info);
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
                    sprintf(info, "Semantics Error: The type of operands with a binary operator \'-\' must be integer or real.");
                    yyerror(this, info);
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
                    sprintf(info, "Semantics Error: The type of operands with a binary operator \'*\' must be integer or real.");
                    yyerror(this, info);
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
                    sprintf(info, "Semantics Error: The type of operands with a binary operator \'/\' must be integer or real.");
                    yyerror(this, info);
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
                    sprintf(info, "Semantics Error: The type of operands with a binary operator \'div\' must be integer or real.");
                    yyerror(this, info);
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
                    sprintf(info, "Semantics Error: The type of operands with a binary operator \'%%\' must be integer.");
                    yyerror(this, info);
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
                    sprintf(info, "Semantics Error: The type of operands with a binary operator \'and\' must be boolean.");
                    yyerror(this, info);
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
                    sprintf(info, "Semantics Error: The type of operands with a binary operator \'or\' must be boolean.");
                    yyerror(this, info);
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
                    sprintf(info, "Semantics Error: The type of operands with a binary operator \'<\' must be integer, real or char.");
                    yyerror(this, info);
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
                    sprintf(info, "Semantics Error: The type of operands with a binary operator \'>\' must be integer, real or char.");
                    yyerror(this, info);
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
                    sprintf(info, "Semantics Error: The type of operands with a binary operator \'<=\' must be integer, real or char.");
                    yyerror(this, info);
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
                    sprintf(info, "Semantics Error: The type of operands with a binary operator \'>=\' must be integer, real or char.");
                    yyerror(this, info);
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
                    sprintf(info, "Semantics Error: The type of operands with a binary operator \'=\' must be integer, real or char.");
                    yyerror(this, info);
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
                    sprintf(info, "Semantics Error: The type of operands with a binary operator \'<>\' must be integer, real or char.");
                    yyerror(this, info);
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
                        sprintf(info, "Semantics Error: Cannot find child named %s in this record.", (((VariableExp *) operand2)->name).c_str());
                        yyerror(this, info);
                        is_legal = false;
                    }
                else {
                    char info[200];
                    sprintf(info, "Semantics Error: The type of the first operand in the binary operator \'.\' must be record.");
                    yyerror(this, info);
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
                        sprintf(info, "Semantics Error: The index must be integer or char.");
                        yyerror(this, info);
                        is_legal = false;
                    }
                else {
                    char info[200];
                    sprintf(info, "Semantics Error: The type of the first operand in the binary operator \'[]\' must be array or string.");
                    yyerror(this, info);
                    is_legal = false;
                }
            }
                break;
            default: {
                char info[200];
                sprintf(info, "Semantics Error: There is something wrong. This operator type is unrecognised.");
                yyerror(this, info);
                is_legal = false;
            }
        }
    return is_legal;
}

bool CallExp::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    // check children
    for (Exp *iter: args)
        is_legal &= iter->checkSemantics();
    // check between children
    // check itself
    FunctionDef *function = findFunction(name, this->father);
    if (function == nullptr) {
        is_legal = false;
        char info[200];
        sprintf(info, "Semantics Error: Cannot find function %s to call.", name.c_str());
        yyerror(this, info);
    }
    else if (args.size() != function->args_type.size()) {
        is_legal = false;
        char info[200];
        sprintf(info, "Semantics Error: The number of arguments are different between call and definition of function %s.", name.c_str());
        yyerror(this, info);
    }
    else {
        for (int i = 0; i < args.size(); i++)
            if (!isSameType(args[i]->return_type, function->args_type[i])) {
                is_legal = false;
                char info[200];
                sprintf(info, "Semantics Error: No.%d argument has different type between call and definition of function %s.", i, name.c_str());
                yyerror(this, info);
                break;
            }
        if (is_legal) return_type = copyType(function->rtn_type);
    }
    return is_legal;
}

bool ConstantExp::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    return_type = generateTypeByValue(value);
    is_legal = true;
    return is_legal;
}

bool VariableExp::checkSemantics() {
#ifdef DEBUG_MODE
    printf("%p\n", this);
#endif
    Base *temp = findName(name, this->father);
    if (temp == nullptr) is_legal = false;
    else
        switch (temp->node_type) {
            case N_CONST_DEF: {
                auto *node = (ConstDef *) temp;
                is_legal = true;
                return_type = node->value->return_type;
                return_value = node->value->return_value;
            }
                break;
            case N_VAR_DEF: {
                auto node = (VarDef *) temp;
                is_legal = true;
                return_type = node->type;
            }
                break;
            case N_ARG_DEF: {
                auto *node = (ArgDef *) temp;
                is_legal = true;
                return_type = node->type;
            }
                break;
            case N_FUNCTION_DEF: {
                auto *node = (FunctionDef *)temp;
                if (node->rtn_type != nullptr) {
                    is_legal = true;
                    return_type = node->rtn_type;
                } else is_legal = false;
            }
                break;
            default:
                is_legal = false;
        }
    return is_legal;
}

#endif
