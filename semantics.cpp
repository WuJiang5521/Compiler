//
// Created by WuJiang on 2018/6/8.
//

#include "tree.h"

using namespace ast;

// block object
bool Program::checkSemantics() {
    is_legal &= define->checkSemantics();
    if (is_legal) is_legal &= body->checkSemantics();
    return is_legal;
}

bool Define::checkSemantics() {
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
    return is_legal;
}

bool Body::checkSemantics() {
    for (Stm *iter: stms)
        is_legal &= iter->checkSemantics();
    return is_legal;
}

bool Situation::checkSemantics() {
    for (Exp *iter: match_list)
        is_legal &= iter->checkSemantics();
    is_legal &= solution->checkSemantics();
    return is_legal;
}

// define object
bool LabelDef::checkSemantics() {

}

bool ConstDef::checkSemantics() {

}

bool TypeDef::checkSemantics() {

}

bool VarDef::checkSemantics() {

}

bool FunctionDef::checkSemantics() {

}

// stm
bool AssignStm::checkSemantics() {

}

bool CallStm::checkSemantics() {

}

bool CaseStm::checkSemantics() {

}

bool ForStm::checkSemantics() {

}

bool GotoStm::checkSemantics() {

}

bool IfStm::checkSemantics() {

}

bool LabelStm::checkSemantics() {

}

bool RepeatStm::checkSemantics() {

}

bool WhileStm::checkSemantics() {

}

// exp
bool UnaryExp::checkSemantics() {

}

bool BinaryExp::checkSemantics() {

}

bool CallExp::checkSemantics() {

}

bool ConstantExp::checkSemantics() {

}

bool VariableExp::checkSemantics() {

}

bool MemoryExp::checkSemantics() {

}

    