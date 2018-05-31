//
// Created by WuJiang on 2018/5/30.
//

#include "tree.h"
#include <utility>

Base::Base(int type) {
    this->node_type = type;
}

Stm::Stm(int type) : Base(type) {}

Exp::Exp(int type) : Base(type) {}

Program::Program(const std::string &name): Base(N_PROGRAM) {
    this->head_name = name;
}

void Program::addDefine(Define *define) {
    if(this->define == nullptr) this->define = define;
}

Define::Define(): Base(N_DEFINE) {
    label_def.clear();
    const_def.clear();
    type_def.clear();
    var_def.clear();
    function_def.clear();
}

void Define::addLabel(LabelDef *def) {
    label_def.push_back(def);
}

void Define::addConst(ConstDef *def) {
    const_def.push_back(def);
}

void Define::addType(TypeDef *def) {
    type_def.push_back(def);
}

void Define::addVar(VarDef *def) {
    var_def.push_back(def);
}

void Define::addFunction(FunctionDef *def) {
    function_def.push_back(def);
}

Body::Body(): Base(N_BODY) {
    stms.clear();
}

void Body::addStm(Stm *stm) {
    stms.push_back(stm);
}

Situation::Situation(): Base(N_SITUATION) {
    match_list.clear();
}

void Situation::addMatch(Exp *exp) {
    match_list.push_back(exp);
}

LabelDef::LabelDef(int index): Base(N_LABEL_DEF) {
    label_index = index;
}

ConstDef::ConstDef(const std::string &name, Exp *val): Base(N_CONST_DEF) {
    this->name = name;
    this->value = val;
}

TypeDef::TypeDef(const std::string &name, Type *type): Base(N_TYPE_DEF) {
    this->name = name;
    this->type = type;
}

VarDef::VarDef(const std::string &name, Type *type): Base(N_VAR_DEF) {
    this->name = name;
    this->type = type;
    this->initializing_value = nullptr;
}

VarDef::VarDef(const std::string &name, Type *type, Value *initialize_value): Base(N_VAR_DEF) {
    this->name = name;
    this->type = type;
    this->initializing_value = initialize_value;
}

FunctionDef::FunctionDef(const std::string &name): Base(N_FUNCTION_DEF) {
    this->name = name;
    args_type.clear();
    args_name.clear();
}

void FunctionDef::addArgs(const std::string &arg_name, Type *arg_type) {
    args_name.push_back(arg_name);
    args_type.push_back(arg_type);
}

void FunctionDef::setReturnType(Type *rtn_type) {
    if(this->rtn_type == nullptr) this->rtn_type = rtn_type;
}

void FunctionDef::addDefine(Define *def) {
    if(define == nullptr) define = def;
}

AssignStm::AssignStm(const std::string &left, Exp *right): Stm(N_ASSIGN_STM) {
    this->left_value = left;
    this->right_value = right;
}

WithStm::WithStm(const std::string &name): Stm(N_WITH_STM) {
    this->name = name;
}

CallStm::CallStm(const std::string &name): Stm(N_CALL_STM) {
    this->name = name;
    args.clear();
}

void CallStm::addArgs(Exp *exp) {
    this->args.push_back(exp);
}

LabelStm::LabelStm(const int &label): Stm(N_LABEL_STM) {
    this->label = label;
}

IfStm::IfStm(): Stm(N_IF_STM) {}

void IfStm::setCondition(Exp *cond) {
    condition = cond;
}

void IfStm::addFalse() {
    this->false_do = new Body();
}

CaseStm::CaseStm(Exp *obj): Stm(N_CASE_STM) {
    object = obj;
    situations.clear();
}

void CaseStm::addSituation(Situation *situation) {
    situations.push_back(situation);
}

ForStm::ForStm(Exp* start, Exp* end, int step): Stm(N_FOR_STM) {
    this->start = start;
    this->end = end;
    this->step = step;
}

WhileStm::WhileStm(Exp *cond): Stm(N_WHILE_STM) {
    condition = cond;
}

RepeatStm::RepeatStm(): Stm(N_REPEAT_STM) {}

void RepeatStm::setCondition(Exp *cond) {
    if (condition == nullptr) condition = cond;
}

GotoStm::GotoStm(int label) : Stm(label) {
    this->label = label;
}

MonocularExp::MonocularExp(int op_code, Exp *oprand) {
    this->op_code = op_code;
    this->operand = oprand;
}

BinaryExp::BinaryExp(int op_code, Exp *operand1, Exp *operand2) {
    this->op_code = op_code;
    this->operand1 = operand1;
    this->operand2 = operand2;
}

CallExp::CallExp(const std::string &name) {
    this->name = name;
    args.clear();
}

void CallExp::addArgs(Exp *exp) {
    args.push_back(exp);
}

ConstantExp::ConstantExp(Value *val) {
    value = val;
}

VariableExp::VariableExp(const std::string &name) {
    this->name = name;
}

MemoryExp::MemoryExp(ADDRESS addr) {
    address = addr;
}

void printTree(Base root, int offset = 0) {
    for (int i = 0; i < offset; i++) printf("  ");
    switch (root.node_type) {
        case N_PROGRAM: {

        }
            break;
        case N_DEFINE: {

        }
            break;
        case N_BODY: {

        }
            break;
        case N_SITUATION: {

        }
            break;
        case N_LABEL_DEF: {

        }
            break;
        case N_CONST_DEF: {

        }
            break;
        case N_TYPE_DEF: {

        }
            break;
        case N_VAR_DEF: {

        }
            break;
        case N_FUNCTION_DEF: {

        }
            break;
        case N_ASSIGN_STM: {

        }
            break;
        case N_CALL_STM: {

        }
            break;
        case N_CASE_STM: {

        }
            break;
        case N_FOR_STM: {

        }
            break;
        case N_GOTO_STM: {

        }
            break;
        case N_IF_STM: {

        }
            break;
        case N_LABEL_STM: {

        }
            break;
        case N_REPEAT_STM: {

        }
            break;
        case N_WHILE_STM: {

        }
            break;
        case N_WITH_STM: {

        }
            break;
        case N_BINARY_EXP: {

        }
            break;
        case N_CALL_EXP: {

        }
            break;
        case N_CONSTANT_EXP: {

        }
            break;
        case N_MEMORY_EXP: {

        }
            break;
        case N_MONOCULAR_EXP: {

        }
            break;
        case N_VARIABLE_EXP: {

        }
            break;
        default: {

        }
    }
}
