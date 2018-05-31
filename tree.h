//
// Created by WuJiang on 2018/5/30.
//

#ifndef SPLCOMPILER_TREE_H
#define SPLCOMPILER_TREE_H

#include <string>
#include <vector>
#include "type.h"
#include "value.h"
#include "common.h"

// reference
// base object
class Base;
class Stm; // has no return value
class Exp; // has return value
// block object
class Program;
class Define;
class Body;
// define object
class LabelDef;
class ConstDef;
class TypeDef;
class VarDef;
class FunctionDef;
// stm
class AssignStm;
class CallStm;
class CaseStm;
class ForStm;
class GotoStm;
class IfStm;
class LabelStm;
class RepeatStm;
class WhileStm;
class WithStm;
// exp
class MonocularExp;
class BinaryExp;
class CallExp;
class ConstantExp;
class VariableExp;
class MemoryExp;
// others
class Situation;

// define
class Base {
public:
    int nodeType;
};

class Stm: public Base {};

class Exp: public Base {};

class Program: public Base {
public:
    std::string head_name;
    Define *define = nullptr; // can be nullptr
    Body *body = nullptr; // cannot be nullptr

    Program();
};

class Define: public Base {
public:
    std::vector<LabelDef> labelDef; // can be empty
    std::vector<ConstDef> constDef; // can be empty
    std::vector<TypeDef> typeDef; // can be empty
    std::vector<VarDef> varDef; // can be empty
    std::vector<FunctionDef> functionDef; // can be empty
};

class Body: public Base {
public:
    std::vector<Stm> stms;
};

class LabelDef: public Base {
public:
    int label_index;
};

class ConstDef: public Base {
public:
    std::string name;
    Type type;
    union {
        bool boolean_value;
        char char_value;
        int integer_value;
        float real_value;
    };
};

class TypeDef: public Base {
public:
    std::string name;
    Type type;
};

class VarDef: public Base {
public:
    std::string name;
    Type type;
    Value initializingValue;
};

class FunctionDef: public Base {
public:
    std::string name;
    std::vector<int> argsType;
    int rtnType;

    Define *Define = nullptr; // can be nullptr
    Body *body = nullptr; // cannot be nullptr
};

class AssignStm: public Stm {
    std::string leftValue;
    Exp rightValue;
};

class WithStm: public Stm {
    std::string name;
    Body body;
};

class CallStm: public Stm {
    std::string name;
};

class LabelStm: public Stm {
    int label;
};

class IfStm: public Stm {
    Exp condition;
    Body *trueDo = nullptr; // cannot be nullptr
    Body *falseDo = nullptr; // can be nullptr
};

class CaseStm: public Stm {
    Exp object;
    std::vector<Situation> situations;
};

class ForStm: public Stm {
    Exp start, end;
    int step; // 1 or -1
    Body loop;
};

class WhileStm: public Stm {
    Exp condition;
    Body loop;
};

class RepeatStm: public Stm {
    Exp condition;
    Body loop;
};

class GotoStm: public Stm {
    int label;
};

class MonocularExp: public Exp {
public:
    int opCode;
    Exp operand;
};

class BinaryExp: public Exp {
public:
    int opCode;
    Exp operand1, operand2;
};

class CallExp: public Exp {
public:
    std::string name;
    std::vector<Exp> args;
};

class ConstantExp: public Exp {
public:
    Value value;
};

class VariableExp: public Exp {
public:
    std::string name;
};

class MemoryExp: public Exp {
public:
    Address address;
};

class Situation: public Base {
    std::vector<Exp> matchList;
    Body solution;
};


#endif //SPLCOMPILER_TREE_H
