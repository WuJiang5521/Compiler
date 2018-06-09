//
// Created by WuJiang on 2018/5/30.
//

#ifndef SPLCOMPILER_TREE_H
#define SPLCOMPILER_TREE_H

#define USE_LLVM

//#define CHECK_SEMANTICS


#ifdef USE_LLVM
#include <llvm/IR/Value.h>
#endif

#include <string>
#include <vector>
#include "common.h"

//codegen
class CodeGenContext;


namespace ast {
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

// type
    class Type;

//value
    class Value;


// define
    class Base {
    public:
        int node_type;
        Base *father = nullptr;
        bool is_legal = true;

        explicit Base(int type = 0);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context) = 0;

#endif
#ifdef CHECK_SEMANTICS

        virtual bool checkSemantics() = 0;

#endif
    };

    class Stm : public Base {
    public:
        explicit Stm(int type = 0);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif
    };

    class Exp : public Base {
    public:
        Value *return_value;
        Type *return_type;

        explicit Exp(int type = 0);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif
    };

    class Body : public Base {
    public:
        std::vector<Stm *> stms;

        Body();

        void addStm(Stm *);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class ExpList : public Base {
    public:
        std::vector<Exp *> exps;

        void addExp(Exp *);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif	
	
#ifdef  CHECK_SEMANTICS
        bool checkSemantics() override { return false;}

#endif
    };

    class Program : public Base {
    public:
        std::string name;
        Define *define = nullptr;
        Body *body = new Body();

        explicit Program(const std::string &);

        void addDefine(Define *);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
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

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class LabelDef : public Base {
    public:
        int label_index;

        explicit LabelDef(int);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class ConstDef : public Base {
    public:
        std::string name;
        Exp *value = nullptr; // cannot be nullptr

        ConstDef(const std::string &, Exp *);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class TypeDef : public Base {
    public:
        std::string name;
        Type *type = nullptr; // cannot be nullptr

        TypeDef(const std::string &, Type *);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class VarDef : public Base {
    public:
        std::string name;
        Type *type = nullptr; // cannot be null
        bool is_global = false;

        VarDef(const std::string &, Type *);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class FunctionDef : public Base {
    public:
        std::string name;
        std::vector<Type *> args_type;
        std::vector <std::string> args_name;
        std::vector<bool> args_is_formal_parameters; //true:&, false:local
        Type *rtn_type = nullptr; //if procedure == nullptr
        Define *define = nullptr;
        Body *body = new Body();

        explicit FunctionDef(const std::string &);

        void addArgs(const std::string &, Type *, bool);

        void setReturnType(Type *);

        void addDefine(Define *);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class ArgDef : public Base {
    public:
        Type *type;

        explicit ArgDef(Type *ty) : Base(N_ARG_DEF) {
            type = ty;
        }

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context) {return nullptr;};

#endif
#ifdef CHECK_SEMANTICS

        bool checkSemantics() override {return false;}

#endif
    };

    class AssignStm : public Stm {
    public:
        Exp *left_value;
        Exp *right_value;

        AssignStm(Exp *, Exp *);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class CallStm : public Stm {
    public:
        std::string name;
        std::vector<Exp *> args;

        explicit CallStm(const std::string &);

        void addArgs(Exp *);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class LabelStm : public Stm {
    public:
        int label;

        explicit LabelStm(const int &);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class IfStm : public Stm {
    public:
        Exp *condition = nullptr;
        Body *true_do = new Body(); // cannot be nullptr
        Body *false_do = nullptr; // can be nullptr

        IfStm();

        void setCondition(Exp *);

        void addFalse();

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class Situation : public Base {
    public:
        std::vector<Exp *> match_list;
        Body *solution = new Body();

        Situation();

        void addMatch(Exp *);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class CaseStm : public Stm {
    public:
        Exp *object;
        std::vector<Situation *> situations;

        explicit CaseStm(Exp *);

        void addSituation(Situation *);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class ForStm : public Stm {
    public:
        std::string iter;
        Exp *start = nullptr, *end = nullptr;
        int step; // 1 or -1
        Body *loop = new Body();

        ForStm(const std::string &, Exp *, Exp *, int);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class WhileStm : public Stm {
    public:
        Exp *condition = nullptr;
        Body *loop = new Body();

        explicit WhileStm(Exp *);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class RepeatStm : public Stm {
    public:
        Exp *condition = nullptr;
        Body *loop = new Body();

        RepeatStm();

        void setCondition(Exp *);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class GotoStm : public Stm {
    public:
        int label;

        explicit GotoStm(int label);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class UnaryExp : public Exp {
    public:
        int op_code;
        Exp *operand;

        UnaryExp(int, Exp *);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class BinaryExp : public Exp {
    public:
        int op_code;
        Exp *operand1, *operand2;

        BinaryExp(int, Exp *, Exp *);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class CallExp : public Exp {
    public:
        std::string name;
        std::vector<Exp *> args;

        explicit CallExp(const std::string &);

        void addArgs(Exp *);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class ConstantExp : public Exp {
    public:
        Value *value;

        explicit ConstantExp(Value *);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class VariableExp : public Exp {
    public:
        std::string name;

        explicit VariableExp(const std::string &);

#ifdef USE_LLVM

        virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

        bool checkSemantics() override;

#endif
    };

    class Type : public Base {
    public:
        std::string name; // use what name to find this value, may be empty
        int base_type; // 0: int 1: real 2: char 3: boolean 5: array 6: record
        // string is considered as an array of char
        int array_start = 0, array_end = 0; // the index for array. useless if the type is not an array
        std::vector<Type *> child_type; // a list of the type of children, there is only one child if the type is array

        Type();

        explicit Type(int base_type);


#ifdef USE_LLVM

        llvm::Type *toLLVMType(CodeGenContext& context);
	    virtual llvm::Value *codeGen(CodeGenContext &context);

#endif

#ifdef CHECK_SEMANTICS

	    bool checkSemantics() override { return false;}

#endif
    };

    class Value {
    public:
        int base_type; // 0: int 1: real 2: char 3: boolean 5: array 6: record
        union return_value {
            INTEGER integer_value;
            REAL real_value;
            CHAR char_value;
            BOOLEAN boolean_value;
            std::string *string_value;
            std::vector<Value *> *children_value; // a list of the value of children
        } val;
#ifdef USE_LLVM

        llvm::Value *codeGen(CodeGenContext &context);

#endif
    };

// example: printTree("log", new Program())
    void printTree(std::string filename, Base *root);

    Type *copyType(Type *origin);

    bool isSameType(Type *type1, Type *type2);

    Base *findName(const std::string &name, Base *node);

    bool canFindLabel(const int &label, Base *node);

    ConstDef *findConst(const std::string &type_name, Base *node);

    Type *findType(const std::string &type_name, Base *node);

    Type *findVar(const std::string &type_name, Base *node);

    FunctionDef *findFunction(const std::string &type_name, Base *node);
}
#endif //SPLCOMPILER_TREE_H
