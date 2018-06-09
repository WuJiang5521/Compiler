#ifndef CODEGEN_H
#define CODEGEN_H

#include <iostream>

#include <stack>
#include <typeinfo>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/ValueSymbolTable.h>
#include <llvm/Bitcode/BitstreamReader.h>
#include <llvm/Bitcode/BitstreamWriter.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/raw_ostream.h>

#include "tree.h"

using namespace llvm;

static llvm::LLVMContext MyContext;

llvm::Function* createPrintf(CodeGenContext& context);

class CodeGenBlock {
public:
    BasicBlock *block;
    llvm::Value *returnValue;
    CodeGenBlock * parent;
    std::map<std::string,  llvm::Value*> locals;
    std::map<std::string, ast::Exp*> const_locals;
    std::map<std::string, ast::Type*> typedefs;
};

class CodeGenContext {
    std::stack<CodeGenBlock *> blocks;
    Function *mainFunction;

public:

    Module *module;
    
    std::map<Function*,Function*> parent;
    Function* currentFunction;
    
    llvm::BasicBlock* labelBlock[10000];
    
    llvm::Function* printf;
    
    
    CodeGenContext() { module = new Module("main", MyContext); }
    
    void generateCode(ast::Program& root);
    GenericValue runCode();
    std::map<std::string,  llvm::Value*>& locals() { return blocks.top()->locals; }
    BasicBlock* currentBlock() { return blocks.top()->block; }
    CodeGenBlock* currentCodeGenBlock() {return blocks.top(); } 
    void pushBlock(BasicBlock *block) { 
      blocks.push(new CodeGenBlock());
      blocks.top()->returnValue = NULL;
      blocks.top()->block = block; 
    }
    void popBlock() {
      CodeGenBlock *top = blocks.top();
      blocks.pop(); 
      delete top;
    }
    void setCurrentReturnValue(llvm::Value *value) { blocks.top()->returnValue = value; }
    llvm::Value* getCurrentReturnValue() { return blocks.top()->returnValue; }
    void insertConst(std::string name, ast::Exp* const_v){
	blocks.top()->const_locals[name] = const_v;
    }
    
    llvm::Value* getValue(std::string name){
        std::cout << "Start getValue for " << name << std::endl;
        std::cout<<"found:"<<currentFunction->getValueSymbolTable()->lookup(name)<<"\n";
        std::cout<<"main:"<<mainFunction<<"\n";
        std::cout<<"current:"<<currentFunction<<"\n";
        llvm::Function* nowFunc = currentFunction;
        if ((nowFunc->getValueSymbolTable()->lookup(name))==NULL) {
            if (module->getGlobalVariable(name)== NULL)
            {
                std::cout << "Undeclared variable " << name << std::endl;
		exit(0);
                return nullptr;
            }
            std::cout << "Found Global Variable:" << name << std::endl;
            return module->getGlobalVariable(name);
        }
        std::cout << "Found Local Variable:" << name << std::endl;
        return nowFunc->getValueSymbolTable()->lookup(name);
    }
    
};


#endif