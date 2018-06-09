//
// Created by WuJiang on 2018/5/30.
//

#include "tree.h"
#include <fstream>

using namespace ast;

Type *ast::copyType(Type *origin) {
    auto *copy = new Type();
    copy->name = origin->name;
    copy->base_type = origin->base_type;
    copy->array_start = origin->array_start;
    copy->array_end = origin->array_end;
    copy->child_type.clear();
    for (Type *iter: origin->child_type)
        copy->child_type.push_back(copyType(iter));
    return copy;
}

bool ast::isSameType(Type *type1, Type *type2) {
    if(type1->base_type == type2->base_type)
        switch (type1->base_type) {
            case TY_INTEGER: case TY_CHAR: case TY_REAL: case TY_BOOLEAN:
                return true;
            case TY_ARRAY:
                if (type1->array_end - type2->array_start == type2->array_end - type2->array_start)
                    return isSameType(type1->child_type[0], type2->child_type[0]);
                break;
            case TY_RECORD:
                if (type1->child_type.size() == type2->child_type.size()) {
                    for (int i = 0; i < type1->child_type.size(); i++)
                        if (!isSameType(type1->child_type[i], type2->child_type[i]))
                            return false;
                    return true;
                }
            default: return false;
        }
    return false;
}

Base *ast::findName(const std::string &name, ast::Base *node) {
    switch (node->node_type) {
        case N_PROGRAM: {
            Define *d_node = ((Program *) node)->define;
            for (ConstDef *iter: d_node->const_def)
                if (iter->name == name) return iter;
            for (TypeDef *iter: d_node->type_def)
                if (iter->name == name) return iter;
            for (VarDef *iter: d_node->var_def)
                if (iter->name == name) return iter;
            for (FunctionDef *iter: d_node->function_def)
                if (iter->name == name) return iter;
            return nullptr;
        }
        case N_FUNCTION_DEF: {
            auto *f_node = (FunctionDef *) node;
            if (f_node->name == name) return f_node;
            for (int i = 0; i < f_node->args_name.size(); i++)
                if (f_node->args_name[i] == name) return new ArgDef(f_node->args_type[i]);
            Define *d_node = f_node->define;
            for (ConstDef *iter: d_node->const_def)
                if(iter->name == name) return iter;
            for (TypeDef *iter: d_node->type_def)
                if(iter->name == name) return iter;
            for (VarDef *iter: d_node->var_def)
                if(iter->name == name) return iter;
            for (FunctionDef *iter: d_node->function_def)
                if(iter->name == name) return iter;
            return findName(name, node->father);
        }
        case N_BODY: case N_SITUATION: case N_LABEL_DEF: case N_CONST_DEF: case N_TYPE_DEF: case N_VAR_DEF: case N_ASSIGN_STM:
        case N_CALL_STM: case N_CASE_STM: case N_FOR_STM: case N_GOTO_STM: case N_IF_STM: case N_LABEL_STM:
        case N_REPEAT_STM: case N_WHILE_STM: case N_BINARY_EXP: case N_CALL_EXP: case N_CONSTANT_EXP:
        case N_DEFINE: case N_UNARY_EXP: case N_VARIABLE_EXP: case N_TYPE:
            return findName(name, node->father);
        default:
            return nullptr;
    }
}

bool ast::canFindLabel(const int &label, Base *node) {
    switch (node->node_type) {
        case N_PROGRAM: {
            Define *d_node = ((Program *)node)->define;
            for (LabelDef *iter: d_node->label_def)
                if(iter->label_index == label) return true;
            return false;
        }
        case N_FUNCTION_DEF: {
            Define *d_node = ((FunctionDef *) node)->define;
            for (LabelDef *iter: d_node->label_def)
                if(iter->label_index == label) return true;
            return ast::canFindLabel(label, node->father);
        }
        case N_BODY: case N_SITUATION: case N_LABEL_DEF: case N_CONST_DEF: case N_TYPE_DEF: case N_VAR_DEF: case N_ASSIGN_STM:
        case N_CALL_STM: case N_CASE_STM: case N_FOR_STM: case N_GOTO_STM: case N_IF_STM: case N_LABEL_STM:
        case N_REPEAT_STM: case N_WHILE_STM: case N_BINARY_EXP: case N_CALL_EXP: case N_CONSTANT_EXP:
        case N_DEFINE: case N_UNARY_EXP: case N_VARIABLE_EXP: case N_TYPE:
            return ast::canFindLabel(label, node->father);
        default:
            return false;
    }
}

ConstDef *findConst(const std::string &type_name, Base *node) {
    Base *result = findName(type_name, node);
    if(result->node_type == N_CONST_DEF) return (ConstDef*)result;
    else return nullptr;
}

Type *ast::findType(const std::string &type_name, Base *node) {
    Base *result = findName(type_name, node);
    if(result->node_type == N_TYPE_DEF) return ((TypeDef*)result)->type;
    else return nullptr;
}

Type *findVar(const std::string &type_name, Base *node) {
    Base *result = findName(type_name, node);
    if(result->node_type == N_VAR_DEF) return ((VarDef*)result)->type;
    else if (result->node_type == N_ARG_DEF) return ((ArgDef*)result)->type;
    else return nullptr;
}

FunctionDef *findFunction(const std::string &type_name, Base *node) {
    Base *result = findName(type_name, node);
    if(result->node_type == N_FUNCTION_DEF) return (FunctionDef*)result;
    else return nullptr;
}

Base::Base(int type) {
    this->node_type = type;
}

Stm::Stm(int type) : Base(type) {}

Exp::Exp(int type) : Base(type) {}

Program::Program(const std::string &name) : Base(N_PROGRAM) {
    this->name = name;
    body->father = this;
}

void Program::addDefine(Define *define) {
    if (this->define == nullptr) {
        define->father = this;
        this->define = define;
    }
}

Define::Define() : Base(N_DEFINE) {
    label_def.clear();
    const_def.clear();
    type_def.clear();
    var_def.clear();
    function_def.clear();
}

void Define::addLabel(LabelDef *def) {
    def->father = this;
    label_def.push_back(def);
}

void Define::addConst(ConstDef *def) {
    def->father = this;
    const_def.push_back(def);
}

void Define::addType(TypeDef *def) {
    def->father = this;
    type_def.push_back(def);
}

void Define::addVar(VarDef *def) {
    def->father = this;
    var_def.push_back(def);
}

void Define::addFunction(FunctionDef *def) {
    def->father = this;
    function_def.push_back(def);
}

void ExpList::addExp(Exp *exp) {
    exps.push_back(exp);
}

Body::Body() : Base(N_BODY) {
    stms.clear();
}

void Body::addStm(Stm *stm) {
    stm->father = this;
    stms.push_back(stm);
}

Situation::Situation() : Base(N_SITUATION) {
    solution->father = this;
    match_list.clear();
}

void Situation::addMatch(Exp *exp) {
    exp->father = this;
    match_list.push_back(exp);
}

LabelDef::LabelDef(int index) : Base(N_LABEL_DEF) {
    label_index = index;
}

ConstDef::ConstDef(const std::string &name, Exp *val) : Base(N_CONST_DEF) {
    val->father = this;
    this->name = name;
    this->value = val;
}

TypeDef::TypeDef(const std::string &name, Type *type) : Base(N_TYPE_DEF) {
    type->father = this;
    this->name = name;
    this->type = type;
}

VarDef::VarDef(const std::string &name, Type *type) : Base(N_VAR_DEF) {
    this->name = name;
    this->type = type;
}

FunctionDef::FunctionDef(const std::string &name) : Base(N_FUNCTION_DEF) {
    this->name = name;
    body->father = this;
    args_type.clear();
    args_name.clear();
}

void FunctionDef::addArgs(const std::string &arg_name, Type *arg_type, bool is_formal_parameter) {
    arg_type->father = this;
    args_name.push_back(arg_name);
    args_type.push_back(arg_type);
    args_is_formal_parameters.push_back(is_formal_parameter);
}

void FunctionDef::setReturnType(Type *rtn_type) {
    if (this->rtn_type == nullptr) {
        rtn_type->father = this;
        this->rtn_type = rtn_type;
    }
}

void FunctionDef::addDefine(Define *def) {
    if (define == nullptr) {
        def->father = this;
        define = def;
    }
}

AssignStm::AssignStm(Exp *left, Exp *right) : Stm(N_ASSIGN_STM) {
    left->father = this;
    right->father = this;
    this->left_value = left;
    this->right_value = right;
}

CallStm::CallStm(const std::string &name) : Stm(N_CALL_STM) {
    this->name = name;
    args.clear();
}

void CallStm::addArgs(Exp *exp) {
    exp->father = this;
    this->args.push_back(exp);
}

LabelStm::LabelStm(const int &label) : Stm(N_LABEL_STM) {
    this->label = label;
}

IfStm::IfStm() : Stm(N_IF_STM) {
    this->true_do->father = this;
}

void IfStm::setCondition(Exp *cond) {
    if (this->condition == nullptr) {
        cond->father = this;
        condition = cond;
    }
}

void IfStm::addFalse() {
    if (this->false_do == nullptr) {
        this->false_do = new Body();
        this->false_do->father = this;
    }
}

CaseStm::CaseStm(Exp *obj) : Stm(N_CASE_STM) {
    obj->father = this;
    object = obj;
    situations.clear();
}

void CaseStm::addSituation(Situation *situation) {
    situation->father = this;
    situations.push_back(situation);
}

ForStm::ForStm(const std::string &iter, Exp *start, Exp *end, int step) : Stm(N_FOR_STM) {
    this->iter = iter;
    this->start = start;
    this->end = end;
    this->step = step;
    start->father = this;
    end->father = this;
    loop->father = this;
}

WhileStm::WhileStm(Exp *cond) : Stm(N_WHILE_STM) {
    condition = cond;
    cond->father = this;
    loop->father = this;
}

RepeatStm::RepeatStm() : Stm(N_REPEAT_STM) {
    loop->father = this;
}

void RepeatStm::setCondition(Exp *cond) {
    if (condition == nullptr) {
        condition = cond;
        cond->father = this;
    }
}

GotoStm::GotoStm(int label) : Stm(label) {
    this->label = label;
}

UnaryExp::UnaryExp(int op_code, Exp *oprand) {
    this->op_code = op_code;
    this->operand = oprand;
    oprand->father = this;
}

BinaryExp::BinaryExp(int op_code, Exp *operand1, Exp *operand2) : Exp(N_BINARY_EXP) {
    this->op_code = op_code;
    this->operand1 = operand1;
    this->operand2 = operand2;
    operand1->father = this;
    operand2->father = this;
}

CallExp::CallExp(const std::string &name) : Exp(N_CALL_EXP) {
    this->name = name;
    args.clear();
}

void CallExp::addArgs(Exp *exp) {
    exp->father = this;
    args.push_back(exp);
}

ConstantExp::ConstantExp(Value *val) : Exp(N_CONSTANT_EXP) {
    value = val;
    return_value = val;
}

VariableExp::VariableExp(const std::string &name) : Exp(N_VARIABLE_EXP) {
    this->name = name;
}

Type::Type() : Base(N_TYPE) {}

Type::Type(int base_type) : Base(N_TYPE) {
    this->base_type = base_type;
}

std::string getString(Value *value) {
    std::string str;
    if (value == nullptr) str = "NULL";
    else
        switch (value->base_type) {
            case TY_INTEGER: {
                char val[10];
                sprintf(val, "%d", value->val.integer_value);
                str.append(val);
            }
                break;
            case TY_REAL: {
                char val[10];
                sprintf(val, "%.2f", value->val.real_value);
                str.append(val);
            }
                break;
            case TY_CHAR: {
                str.append("\'");
                char val[2];
                sprintf(val, "%c", value->val.char_value);
                str.append(val);
                str.append("\'");
            }
                break;
            case TY_BOOLEAN: {
                str.append(value->val.boolean_value ? "true" : "false");
            }
                break;
            case TY_ARRAY:
            case TY_RECORD: {
                str.append("[");
                for (auto child: *value->val.children_value) {
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
                str.append("\"name\":\"");
                str.append(node->name);
                str.append("\",");
                str.append("\"define\":");
                str.append(getString(node->define));
                str.append(",");
                str.append("\"body\":");
                str.append(getString(node->body));
                str.append(",}");
            }
                break;
            case N_DEFINE: {
                auto *node = (Define *) ori_node;
                str.append("{");
                str.append("\"label\": [");
                for (auto stm: node->label_def) {
                    str.append(getString(stm));
                    str.append(",");
                }
                str.append("],");
                str.append("\"const\": [");
                for (auto stm: node->const_def) {
                    str.append(getString(stm));
                    str.append(",");
                }
                str.append("],");
                str.append("\"type\": [");
                for (auto stm: node->type_def) {
                    str.append(getString(stm));
                    str.append(",");
                }
                str.append("],");
                str.append("\"var\": [");
                for (auto stm: node->var_def) {
                    str.append(getString(stm));
                    str.append(",");
                }
                str.append("],");
                str.append("\"function\": [");
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
                str.append("{\"match_list\":[");
                for (auto match_item: node->match_list) {
                    str.append(getString(match_item));
                    str.append(",");
                }
                str.append("], \"to_do\":");
                str.append(getString(node->solution));
                str.append("}");
            }
                break;
            case N_LABEL_DEF: {
                auto *node = (LabelDef *) ori_node;
                str.append("{\"label_def\": ");
                char id[100];
                sprintf(id, "%d", node->label_index);
                str.append(id);
                str.append("}");
            }
                break;
            case N_CONST_DEF: {
                auto *node = (ConstDef *) ori_node;
                str.append("{\"const_name\": \"");
                str.append(node->name);
                str.append("\", \"const_value\": ");
                str.append(getString(node->value));
                str.append("}");
            }
                break;
            case N_TYPE_DEF: {
                auto *node = (TypeDef *) ori_node;
                str.append("{\"type_name\": \"");
                str.append(node->name);
                str.append("\", \"structure\": ");
                str.append(getString(node->type));
                str.append("}");
            }
                break;
            case N_VAR_DEF: {
                auto *node = (VarDef *) ori_node;
                str.append("{\"var_name\": \"");
                str.append(node->name);
                str.append("\", \"structure\": ");
                str.append(getString(node->type));
                str.append("}");
            }
                break;
            case N_FUNCTION_DEF: {
                auto *node = (FunctionDef *) ori_node;
                str.append("{\"func_name\": \"");
                str.append(node->name);
                str.append("\", \"args\": [");
                for (int i = 0; i < node->args_name.size(); i++) {
                    str.append("{\"arg_name\":\"");
                    str.append(node->args_name[i]);
                    str.append("\", \"arg_type\":");
                    str.append(getString(node->args_type[i]));
                    str.append("\", \"arg_is_formal_parameter\":");
                    str.append(node->args_is_formal_parameters[i] ? "true" : "false");
                    str.append("},");
                }
                str.append("]");
                if (node->rtn_type != nullptr) {
                    str.append(", \"return_type\": ");
                    str.append(getString(node->rtn_type));
                }
                if (node->define != nullptr) {
                    str.append(", \"defines\": ");
                    str.append(getString(node->define));
                }
                str.append(", \"body\": ");
                str.append(getString(node->body));
                str.append("}");
            }
                break;
            case N_ASSIGN_STM: {
                auto *node = (AssignStm *) ori_node;
                str.append("{\"left\":\"");
                str.append(getString(node->left_value));
                str.append("\",\"right\":");
                str.append(getString(node->right_value));
                str.append("}");
            }
                break;
            case N_CALL_STM: {
                auto *node = (CallStm *) ori_node;
                str.append("{\"func\":\"");
                str.append(node->name);
                str.append("\",\"args\":[");
                for (auto arg: node->args) {
                    str.append(getString(arg));
                    str.append(",");
                }
                str.append("]}");
            }
                break;
            case N_CASE_STM: {
                auto *node = (CaseStm *) ori_node;
                str.append("{\"switch_item\":\"");
                str.append(getString(node->object));
                str.append("\",\"situations\":[");
                for (auto situation: node->situations) {
                    str.append(getString(situation));
                    str.append(",");
                }
                str.append("]}");
            }
                break;
            case N_FOR_STM: {
                auto *node = (ForStm *) ori_node;
                str.append("{\"iter\":\"");
                str.append(node->iter);
                str.append("\",\"start\":");
                str.append(getString(node->start));
                str.append(",\"end\":");
                str.append(getString(node->end));
                str.append(",\"step\":");
                if (node->step == 1) str.append("1");
                else str.append("-1");
                str.append(",\"body\":");
                str.append(getString(node->loop));
                str.append("]}");
            }
                break;
            case N_GOTO_STM: {
                auto *node = (GotoStm *) ori_node;
                str.append("{\"goto\":");
                char label[100];
                sprintf(label, "%d", node->label);
                str.append(label);
                str.append("}");
            }
                break;
            case N_IF_STM: {
                auto *node = (IfStm *) ori_node;
                str.append("{\"condition\":");
                str.append(getString(node->condition));
                str.append(",\"true_body\":");
                str.append(getString(node->true_do));
                if (node->false_do != nullptr) {
                    str.append(",\"false_body\":");
                    str.append(getString(node->false_do));
                }
                str.append("}");
            }
                break;
            case N_LABEL_STM: {
                auto *node = (LabelStm *) ori_node;
                str.append("{\"label\": ");
                char id[100];
                sprintf(id, "%d", node->label);
                str.append(id);
                str.append("}");
            }
                break;
            case N_REPEAT_STM: {
                auto *node = (RepeatStm *) ori_node;
                str.append("{\"body\":");
                str.append(getString(node->loop));
                str.append(",\"condition\":");
                str.append(getString(node->condition));
                str.append("}");
            }
                break;
            case N_WHILE_STM: {
                auto *node = (WhileStm *) ori_node;
                str.append("{\"condition\":");
                str.append(getString(node->condition));
                str.append(",\"body\":");
                str.append(getString(node->loop));
                str.append("}");
            }
                break;
            case N_BINARY_EXP: {
                auto *node = (BinaryExp *) ori_node;
                str.append("{\"bin_op\":\"");
                str.append(getOpNameByID(node->op_code));
                str.append("\",\"operand1\":");
                str.append(getString(node->operand1));
                str.append("\",\"operand2\":");
                str.append(getString(node->operand2));
                str.append("}");
            }
                break;
            case N_CALL_EXP: {
                auto *node = (CallExp *) ori_node;
                str.append("{\"func\":\"");
                str.append(node->name);
                str.append("\",\"args\":[");
                for (auto arg: node->args) {
                    str.append(getString(arg));
                    str.append(",");
                }
                str.append("]}");
            }
                break;
            case N_CONSTANT_EXP: {
                auto *node = (ConstantExp *) ori_node;
                str.append("{\"const_value\":");
                str.append(getString(node->value));
                str.append("}");
            }
                break;
            case N_UNARY_EXP: {
                auto *node = (UnaryExp *) ori_node;
                str.append("{\"mon_op\":\"");
                str.append(getOpNameByID(node->op_code));
                str.append("\",\"operand\":");
                str.append(getString(node->operand));
                str.append("}");
            }
                break;
            case N_VARIABLE_EXP: {
                auto *node = (VariableExp *) ori_node;
                str.append("{\"var_name\":\"");
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
                    case TY_ARRAY: {
                        str.append("{\"type\":\"array\",\"start_index\":");
                        char num[100];
                        sprintf(num, "%d", node->array_start);
                        str.append(num);
                        str.append(",\"end_index\":");
                        sprintf(num, "%d", node->array_end);
                        str.append(num);
                        str.append(",\"child_type\":");
                        str.append(getString(node->child_type[0]));
                        str.append("}");
                    }
                        break;
                    case TY_RECORD: {
                        str.append("{\"type\":\"record\",\"child_type\":[");
                        for (auto child: node->child_type) {
                            str.append("{\"name\":\"");
                            str.append(child->name);
                            str.append("\", \"type\":");
                            str.append(getString(child));
                            str.append("},");
                        }
                        str.append("]}");
                    }
                        break;
                        /*
                        default: {
                            if (node->base_type < type_list.size()) str.append(type_list[node->base_type]->name);
                            else str.append("\"There is something wrong. The type cannot be recognised.\"");
                        }
                        */
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
