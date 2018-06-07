//
// Created by WuJiang on 2018/5/30.
//

#ifndef SPLCOMPILER_TREE_H
#define SPLCOMPILER_TREE_H

#include <llvm/IR/Value.h>

#include <string>
#include <vector>
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
#define N_BINARY_EXP 40
#define N_CALL_EXP 41
#define N_CONSTANT_EXP 42
#define N_UNARY_EXP 43
#define N_VARIABLE_EXP 44
#define N_TYPE 50
// type code
#define TY_INTEGER 0
#define TY_REAL 1
#define TY_CHAR 2
#define TY_BOOLEAN 3
#define TY_ARRAY 4
#define TY_RECORD 5

//codegen
class CodeGenContext;


namespace ast{
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
// exp
class UnaryExp;
class BinaryExp;
class CallExp;
class ConstantExp;
class VariableExp;
class MemoryExp;
// type
class Type;
//value
class Value;


// define
class Base {
public:
    int node_type;
    Base *father = nullptr;

    explicit Base(int type = 0);

    virtual llvm::Value* codeGen(CodeGenContext& context) = 0;
};

class Stm : public Base {
public:
    explicit Stm(int type = 0);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Exp : public Base {
public:
    Value *return_value;
    Type *return_type;

    explicit Exp(int type = 0);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Body : public Base {
public:
    std::vector<Stm *> stms;

    Body();

    void addStm(Stm *);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class ExpList : public Base {
public:
    std::vector<Exp *> exps;
    void addExp(Exp*);
};

class Program : public Base {
public:
    std::string name;
    Define *define = nullptr;
    Body *body = new Body();

    explicit Program(const std::string &);

    void addDefine(Define *);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Define : public Base {
public:
    std::vector<LabelDef *> label_def; // can be empty
    std::vector<ConstDef *> const_def; // can be empty
    std::vector<TypeDef *> type_def; // can be empty
    std::vector<VarDef *> var_def; // can be empty
    std::vector<FunctionDef *> function_def; // can be empty

    Define();

    void addLabel(LabelDef *);

    void addConst(ConstDef *);

    void addType(TypeDef *);

    void addVar(VarDef *);

    void addFunction(FunctionDef *);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class LabelDef : public Base {
public:
    int label_index;

    explicit LabelDef(int);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class ConstDef : public Base {
public:
    std::string name;
    Exp *value = nullptr; // cannot be nullptr

    ConstDef(const std::string &, Exp *);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class TypeDef : public Base {
public:
    std::string name;
    Type *type = nullptr; // cannot be nullptr

    TypeDef(const std::string &, Type *);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class VarDef : public Base {
public:
    std::string name;
    Type *type = nullptr; // cannot be null
    bool is_global = false;

    VarDef(const std::string &, Type *);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class FunctionDef : public Base {
public:
    std::string name;
    std::vector<Type *> args_type;
    std::vector<std::string> args_name;
    std::vector<bool> args_is_formal_parameters; //true:&, false:local
    Type *rtn_type = nullptr; //if procedure == nullptr
    Define *define = nullptr;
    Body *body = new Body();

    explicit FunctionDef(const std::string &);

    void addArgs(const std::string &, Type *, bool);

    void setReturnType(Type *);

    void addDefine(Define *);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class AssignStm : public Stm {
public:
    Exp *left_value;
    Exp *right_value;

    AssignStm(Exp*, Exp *);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class CallStm : public Stm {
public:
    std::string name;
    std::vector<Exp *> args;

    explicit CallStm(const std::string &);

    void addArgs(Exp *);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class LabelStm : public Stm {
public:
    int label;

    explicit LabelStm(const int &);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class IfStm : public Stm {
public:
    Exp *condition = nullptr;
    Body *true_do = new Body(); // cannot be nullptr
    Body *false_do = nullptr; // can be nullptr

    IfStm();

    void setCondition(Exp *);

    void addFalse();

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Situation : public Base {
public:
    std::vector<Exp *> match_list;
    Body *solution = new Body();

    Situation();

    void addMatch(Exp *);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class CaseStm : public Stm {
public:
    Exp *object;
    std::vector<Situation *> situations;

    explicit CaseStm(Exp *);

    void addSituation(Situation *);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class ForStm : public Stm {
public:
    std::string iter;
    Exp *start = nullptr, *end = nullptr;
    int step; // 1 or -1
    Body *loop = new Body();

    ForStm(const std::string &, Exp *, Exp *, int);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class WhileStm : public Stm {
public:
    Exp *condition = nullptr;
    Body *loop = new Body();

    explicit WhileStm(Exp *);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class RepeatStm : public Stm {
public:
    Exp *condition = nullptr;
    Body *loop = new Body();

    RepeatStm();

    void setCondition(Exp *);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class GotoStm : public Stm {
public:
    int label;

    explicit GotoStm(int label);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class UnaryExp: public Exp {
public:
    int op_code;
    Exp *operand;

    UnaryExp(int, Exp*);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class BinaryExp : public Exp {
public:
    int op_code;
    Exp *operand1, *operand2;

    BinaryExp(int, Exp *, Exp *);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class CallExp : public Exp {
public:
    std::string name;
    std::vector<Exp *> args;

    explicit CallExp(const std::string &);

    void addArgs(Exp *);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class ConstantExp : public Exp {
public:
    Value *value;

    explicit ConstantExp(Value *);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class VariableExp : public Exp {
public:
    std::string name;

    explicit VariableExp(const std::string &);

    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Type : public Base {
public:
    std::string name; // use what name to find this value, may be empty
    int base_type; // 0: int 1: real 2: char 3: boolean 4: set 5: array 6: record 7~n: other type defined by user
    // string is considered as an array of char
    int array_start = 0, array_end = 0; // the index for array. useless if the type is not an array
    std::vector<Type *> child_type; // a list of the type of children, there is only one child if the type is array

    Type();

    llvm::Type* toLLVMType(void);
};

class Value {
public:
    int base_type; // 0: int 1: real 2: char 3: boolean 4: string 5: array 6: record
    ADDRESS address;
	union return_value {
	    INTEGER integer_value;
	    REAL real_value;
	    CHAR char_value;
	    BOOLEAN boolean_value;
	    std::string* string_value;
	    std::vector<Value*>* children_value; // a list of the value of children
	} val;
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

// example: printTree("log", new Program())
void printTree(std::string filename, Base *root);

// example: Type *type = findType("arr");
Type *findType(const std::string &type_name, Base *node);
}
#endif //SPLCOMPILER_TREE_H
