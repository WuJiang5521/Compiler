//
// Created by WuJiang on 2018/5/30.
//

#ifndef SPLCOMPILER_TREE_H
#define SPLCOMPILER_TREE_H

#include <string>
#include <vector>
#include "value.h"
#include "common.h"

// node type
#define N_PROGRAM 0
#define N_DEFINE 1
#define N_BODY 2
#define N_SITUATION 3
#define N_LABEL_DEF 10
#define N_CONST_DEF 11
#define N_TYPE_DEF 12
#define N_VAR_DEF 13
#define N_FUNCTION_DEF 14
#define N_ASSIGN_STM 20
#define N_CALL_STM 21
#define N_CASE_STM 22
#define N_FOR_STM 23
#define N_GOTO_STM 24
#define N_IF_STM 25
#define N_LABEL_STM 26
#define N_REPEAT_STM 27
#define N_WHILE_STM 28
#define N_WITH_STM 29
#define N_BINARY_EXP 40
#define N_CALL_EXP 41
#define N_CONSTANT_EXP 42
#define N_MEMORY_EXP 43
#define N_MONOCULAR_EXP 44
#define N_VARIABLE_EXP 45
#define N_TYPE 50
// type code
#define T_INTEGER 0
#define T_REAL 1
#define T_CHAR 2
#define T_BOOLEAN 3
#define T_SET 4
#define T_ARRAY 5
#define T_RECORD 6

// base object
class Base;
class Stm; // has no return value
class Exp; // has return value
// block object
class Program;
class Define;
class Body;
class Situation;
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
// type
class Type;

// define
class Base {
public:
    int node_type;

    explicit Base(int type = 0);
};

class Stm: public Base {
public:
    explicit Stm(int type = 0);
};

class Exp: public Base {
public:
    Value return_value;

    explicit Exp(int type = 0);
};

class Program: public Base {
public:
    std::string name;
    Define *define = nullptr;
    Body *body = new Body();

    explicit Program(const std::string &);
    void addDefine(Define*);
};

class Define: public Base {
public:
    std::vector<LabelDef*> label_def; // can be empty
    std::vector<ConstDef*> const_def; // can be empty
    std::vector<TypeDef*> type_def; // can be empty
    std::vector<VarDef*> var_def; // can be empty
    std::vector<FunctionDef*> function_def; // can be empty

    Define();
    void addLabel(LabelDef*);
    void addConst(ConstDef*);
    void addType(TypeDef*);
    void addVar(VarDef*);
    void addFunction(FunctionDef*);
};

class Body: public Base {
public:
    std::vector<Stm*> stms;

    Body();
    void addStm(Stm*);
};

class Situation: public Base {
public:
    std::vector<Exp*> match_list;
    Body *solution = new Body();

    Situation();
    void addMatch(Exp*);
};

class LabelDef: public Base {
public:
    int label_index;

    explicit LabelDef(int);
};

class ConstDef: public Base {
public:
    std::string name;
    Exp *value = nullptr; // cannot be nullptr

    ConstDef(const std::string &, Exp*);
};

class TypeDef: public Base {
public:
    std::string name;
    Type *type = nullptr; // cannot be nullptr

    TypeDef(const std::string &, Type*);
};

class VarDef: public Base {
public:
    std::string name;
    Type *type = nullptr; // cannot be null
    Value *initializing_value = nullptr; // can be null

    VarDef(const std::string &, Type*);
    VarDef(const std::string &, Type*, Value*);
};

class FunctionDef: public Base {
public:
    std::string name;
    std::vector<Type*> args_type;
    std::vector<std::string> args_name;
    Type *rtn_type = nullptr;
    Define *define = nullptr;
    Body *body = new Body();

    explicit FunctionDef(const std::string &);
    void addArgs(const std::string &, Type*);
    void setReturnType(Type*);
    void addDefine(Define*);
};

class AssignStm: public Stm {
public:
    std::string left_value;
    Exp *right_value;

    AssignStm(const std::string&, Exp*) = default;
};

class WithStm: public Stm {
public:
    std::string name;
    Body *body = new Body();

    explicit WithStm(const std::string&);
};

class CallStm: public Stm {
public:
    std::string name;
    std::vector<Exp *> args;

    explicit CallStm(const std::string &);
    void addArgs(Exp *);
};

class LabelStm: public Stm {
public:
    int label;

    explicit LabelStm(const int &);
};

class IfStm: public Stm {
public:
    Exp *condition = nullptr;
    Body *true_do = new Body(); // cannot be nullptr
    Body *false_do = nullptr; // can be nullptr

    IfStm() = default;
    void setCondition(Exp *);
    void addFalse();
};

class CaseStm: public Stm {
public:
    Exp *object;
    std::vector<Situation*> situations;

    explicit CaseStm(Exp *);
    void addSituation(Situation *);
};

class ForStm: public Stm {
public:
    std::string iter;
    Exp *start = nullptr, *end = nullptr;
    int step; // 1 or -1
    Body *loop = new Body();

    ForStm(const std::string &, Exp*, Exp*, int) = default;
};

class WhileStm: public Stm {
public:
    Exp *condition = nullptr;
    Body *loop = new Body();

    explicit WhileStm(Exp *);
};

class RepeatStm: public Stm {
public:
    Exp *condition = nullptr;
    Body *loop = new Body();

    RepeatStm() = default;
    void setCondition(Exp *);
};

class GotoStm: public Stm {
public:
    int label;

    explicit GotoStm(int label);
};

class MonocularExp: public Exp {
public:
    int op_code;
    Exp *operand;

    MonocularExp(int, Exp*);
};

class BinaryExp: public Exp {
public:
    int op_code;
    Exp *operand1, *operand2;

    BinaryExp(int, Exp*, Exp*);
};

class CallExp: public Exp {
public:
    std::string name;
    std::vector<Exp*> args;

    explicit CallExp(const std::string &);
    void addArgs(Exp *);
};

class ConstantExp: public Exp {
public:
    Value *value;

    explicit ConstantExp(Value *);
};

class VariableExp: public Exp {
public:
    std::string name;

    explicit VariableExp(const std::string &);
};

class MemoryExp: public Exp {
public:
    ADDRESS address;

    explicit MemoryExp(ADDRESS address);
};

class Type: public Base {
public:
    std::string name; // use what name to find this value, may be empty
    int base_type; // 0: int 1: real 2: char 3: boolean 4: set 5: array 6: record 7~n: other type defined by user
                   // string is considered as an array of char
    int children_num; // the number of children
    std::vector<Type*> child_type; // a list of the type of children

    Type();
};

// example: printTree("log", new Program())
void printTree(std::string filename, Base *root);
// example: addType(new Type())
void addType(Type *type);
// example: Type *type = findType("arr");
Type *findType(std::string type_name);

extern std::vector<Type*> type_list;

#endif //SPLCOMPILER_TREE_H
