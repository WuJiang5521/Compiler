#include <iostream>
#include <vector>

#include "codegen.h"
#include "tree.h"

using namespace ast;

/* Compile the AST into a module */
void CodeGenContext::generateCode(Program& root)
{
	std::cout << "Generating code...\n";
	
	/* Create the top level interpreter function to call as entry */
	std::vector<llvm::Type*> argTypes;
	FunctionType *ftype = FunctionType::get(llvm::Type::getVoidTy(MyContext), makeArrayRef(argTypes), false);
	mainFunction = Function::Create(ftype, GlobalValue::InternalLinkage, "main", module);
	BasicBlock *bblock = BasicBlock::Create(MyContext, "entry", mainFunction, 0);
	
	/* Push a new variable/block context */
	pushBlock(bblock);
	root.codeGen(*this); /* emit bytecode for the toplevel block */
	ReturnInst::Create(MyContext, bblock);
	popBlock();
	
	/* Print the bytecode in a human-readable format 
	   to see if our program compiled properly
	 */
	std::cout << "Code is generated.\n";
	// module->dump();

	legacy::PassManager pm;
	pm.add(createPrintModulePass(outs()));
	pm.run(*module);
}

/* Executes the AST by running the main function */
GenericValue CodeGenContext::runCode() {
	std::cout << "Running code...\n";
	ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module) ).create();
	ee->finalizeObject();
	std::vector<GenericValue> noargs;
	GenericValue v = ee->runFunction(mainFunction, noargs);
	std::cout << "Code run.\n";
	return v;
}

//--------------------------------------------------------------
//--------------------------------------------------------------
//codeGen functions in tree.h

//helper function:
llvm::Type* ast::Type::toLLVMType(CodeGenContext& context){// 0: int 1: real 2: char 3: boolean 4: set 5: array 6: record 7~n: other type defined by user
    switch(base_type){
      case TY_INTEGER: return llvm::Type::getInt32Ty(MyContext);
      case TY_REAL: return llvm::Type::getDoubleTy(MyContext);
      case TY_CHAR: return llvm::Type::getInt8Ty(MyContext);
      case TY_BOOLEAN: return llvm::Type::getInt1Ty(MyContext);
      case TY_SET: return nullptr;
      case TY_ARRAY: return llvm::ArrayType::get(this->toLLVMType(context), array_end - array_start + 1);
      case TY_RECORD: {
	std::vector<llvm::Type*> members;
	LLVMContext ctx;
	for(auto child:child_type){
	    members.push_back(child->toLLVMType(context));
	}
	StructType*const llvm_S = StructType::create(MyContext, name);StructType::get(MyContext, members);
	llvm_S->setBody(members);
	return llvm_S;
      }
      default: 
	CodeGenBlock* currBlock = context.currentCodeGenBlock();
	while(currBlock != nullptr){  
	  auto typetable = currBlock->typedefs;
	  if(typetable.find(name))
	    return typetable[name]->toLLVMType();
	  currBlock = currBlock->parent;
	}
	std::cout << "undefined type name: " << name << std::endl;
	exit(0);
    }
}

llvm::Value* Stm::codeGen(CodeGenContext& context){
  //do nothing
}

llvm::Value* Exp::codeGen(CodeGenContext& context){
  //do nothing
}

llvm::Value* Body::codeGen(CodeGenContext& context){
  for(auto sub_stm: stms){
    sub_stm->codeGen(context);
  }
}

llvm::Value* ExpList::codeGen(CodeGenContext& context){
  for(auto sub_exp: exps){
    sub_exp->codeGen(context);
  }
}

llvm::Value* Program::codeGen(CodeGenContext& context){
  llvm::Value* last = nullptr;
  std::cout << "program----head" << std::endl;
  
  if(define != nullptr){
    for(auto const_d:define->const_def){
      last = const_d->codeGen(context);
    }
    std::cout << "program----const_done" << std::endl;
    for(auto var_d:define->var_def){
      var_d->is_global = true;
      last = var_d->codeGen(context);
    }
    std::cout << "program----var_done" << std::endl;
    for(auto fun_d:define->function_def){
      last = fun_d->codeGen(context);
    }
    std::cout << "program----functiondef_done" << std::endl;
  }
  
  body->codeGen(context);
  std::cout << "program----body_done" << std::endl;
  
  return last;
}

llvm::Value* Define::codeGen(CodeGenContext& context){
  //do nothing
}

llvm::Value* Situation::codeGen(CodeGenContext& context){
  //do nothing because CaseStm did everything
}

llvm::Value* LabelDef::codeGen(CodeGenContext& context){
  //don't know what to do
}

llvm::Value* ConstDef::codeGen(CodeGenContext& context){
  std::cout << "creating const: " << name << std::endl;
  auto alloc = new llvm::AllocaInst(value->return_type->toLLVMType(context), 0,  name.c_str(), context.currentBlock());
  auto store = new llvm::StoreInst(value->return_value->codeGen(context), alloc, false, context.currentBlock());
  context.insertConst(name, value);
  return store;
}

llvm::Value* TypeDef::codeGen(CodeGenContext& context){
  context.currentCodeGenBlock()->typedefs[name] = type;
}

llvm::Value* VarDef::codeGen(CodeGenContext& context){
  std::cout << "variable define: " << name << std::endl;
  llvm::Value* alloc;
  if(is_global){
    std::cout << "<global-variable>" << name << std::endl;
    if(type->array_end != 0 || type->array_start != 0 ){//is array
      std::cout << " |__is an array" << std::endl;
      auto vec = std::vector<llvm::Constant*>();
      llvm::Constant* ele_of_arr;
      switch(type->base_type){
	case TY_INTEGER: ele_of_arr = llvm::ConstantInt::get(llvm::Type::getInt32Ty(MyContext), 0, true);  break;
	case TY_REAL: ele_of_arr = llvm::ConstantFP::get(llvm::Type::getDoubleTy(MyContext), 0);    break;
	case TY_CHAR: ele_of_arr = llvm::ConstantInt::get(llvm::Type::getInt8Ty(MyContext), 0, true);     break;
	case TY_BOOLEAN: ele_of_arr = llvm::ConstantInt::get(llvm::Type::getInt1Ty(MyContext), 0, true);     break;
	default: ;
	//don't know yet
      }
      for(int i = 0; i < (type->array_end - type->array_start + 1); i++){
	vec.push_back(ele_of_arr);
      }
      auto arr_type_0 = (llvm::ArrayType*) type->toLLVMType(context);
      auto arr_const = llvm::ConstantArray::get(arr_type_0, vec);
      
      auto go = new llvm::GlobalVariable(*context.module, type->toLLVMType(context),
					 false, llvm::GlobalValue::ExternalLinkage, arr_const, name);
      alloc = go;
    }
    else{
      switch(type->base_type){
	case TY_INTEGER: {
	  auto go = new llvm::GlobalVariable(*context.module, type->toLLVMType(context),
					 false, llvm::GlobalValue::ExternalLinkage ,llvm::ConstantInt::get(llvm::Type::getInt32Ty(MyContext), 0, true), name);
					 alloc = go;
					 break;
	}
	case TY_REAL: { 
	  auto go = new llvm::GlobalVariable(*context.module, type->toLLVMType(context),
					 false, llvm::GlobalValue::ExternalLinkage , llvm::ConstantFP::get(llvm::Type::getDoubleTy(MyContext), 0), name);
					 alloc = go;
					 break;
	}
	case TY_CHAR: {
	  auto go = new llvm::GlobalVariable(*context.module, type->toLLVMType(context),
					 false, llvm::GlobalValue::ExternalLinkage , llvm::ConstantInt::get(llvm::Type::getInt8Ty(MyContext), 0, true), name);
					 alloc = go;
					 break;
	}
	case TY_BOOLEAN: {
	  auto go = new llvm::GlobalVariable(*context.module, type->toLLVMType(context),
					 false, llvm::GlobalValue::ExternalLinkage , llvm::ConstantInt::get(llvm::Type::getInt1Ty(MyContext), 0, true), name);
					 alloc = go;
					 break;
	}
	default: ;
	//don't know yet
      }
    }
  }
  else{
    alloc = new llvm::AllocaInst(type->toLLVMType(context), 0, name.c_str(), context.currentBlock());
  }
  std::cout << "variable define finished" << std::endl;
  return alloc;
}

llvm::Value* FunctionDef::codeGen(CodeGenContext& context){
    std::vector<llvm::Type*> arg_types;
    for(ast::Type *it : args_type)
      arg_types.push_back(it->toLLVMType(context)); 
    auto f_type = llvm::FunctionType::get((rtn_type == nullptr) ? llvm::Type::getVoidTy(MyContext) : rtn_type->toLLVMType(context), llvm::makeArrayRef(arg_types), false);
    auto function = llvm::Function::Create(f_type, llvm::GlobalValue::InternalLinkage, name.c_str(), context.module);
    auto block = llvm::BasicBlock::Create(MyContext, "entry", function,NULL);
    auto oldFunc = context.currentFunction;
    context.currentFunction = function;
    auto oldBlock = context.currentBlock();
    context.parent[function] = oldFunc;
    // push block and start routine
    context.pushBlock(block);
    
    llvm::Value* arg_value;
    auto args_values = function->arg_begin();
    for(int i = 0; i < arg_types.size(); i++){
      std::cout << "variable define: " << name << std::endl;
      llvm::Value* alloc;
      alloc = new llvm::AllocaInst(args_type[i]->toLLVMType(context), 0, name.c_str(), context.currentBlock());
      arg_value = args_values++;
      arg_value->setName(args_name[i].c_str());
      auto inst = new llvm::StoreInst(arg_value, context.getValue(args_name[i]), false, block);
    }
    
    if(rtn_type != nullptr){
      std::cout << "creating function return value declaration" << std::endl;
      auto alloc = new llvm::AllocaInst(rtn_type->toLLVMType(context), 0, name.c_str(), context.currentBlock());
    }
    
    std::cout << "function header part success!" << std::endl;
    
    //function Vars
    if(define){
        for(auto var_d: define->var_def) {
	  var_d->codeGen(context);
	}
	
	for(auto func_d: define->function_def){
	  func_d->codeGen(context);
	}
    }
    
    std::cout << "function var part success!" << std::endl;
    //body
    body->codeGen(context);
    
    // return value

    
    if (rtn_type != nullptr) {
        std::cout << "Generating return value for function" << std::endl;
        auto load_ret = new llvm::LoadInst(context.getValue(name), "", false, context.currentBlock());
        llvm::ReturnInst::Create(MyContext, load_ret, context.currentBlock());
    }
    else{
        std::cout << "Generating return void for procedure" << std::endl;
        llvm::ReturnInst::Create(MyContext, context.currentBlock());
        
    }

    // pop block and finsh
    while (context.currentBlock() != oldBlock)
        context.popBlock();
    context.currentFunction = oldFunc;
    std::cout << "create " << name << "finished" << std::endl;
    return function;
}

llvm::Value* AssignStm::codeGen(CodeGenContext& context){
  
}

llvm::Value* WithStm::codeGen(CodeGenContext& context){
  
}

llvm::Value* CallStm::codeGen(CodeGenContext& context){
  
}

llvm::Value* LabelStm::codeGen(CodeGenContext& context){
  
}

llvm::Value* IfStm::codeGen(CodeGenContext& context){
  
}

llvm::Value* CaseStm::codeGen(CodeGenContext& context){
  BasicBlock* bexit = BasicBlock::Create(MyContext, "exit", context.currentFunction);

    std::vector<BasicBlock *> bblocks;
    std::cout<< "this switch contains :" << situations.size() << "cases" <<std::endl;
   
    for (int i=0;i < situations.size();i++){ 
	for(int j = 0; j < situations[i]->match_list.size(); j++){
	  auto bblock = BasicBlock::Create(MyContext, "caseStmt", context.currentFunction);
	  bblocks.push_back(bblock);
	}
    }
    
    int p = 0;
    int i, j;
    for (i = 0;i < situations.size();i++, p++){ 
	for(j = 0; j < situations[i]->match_list.size(); j++, p++){
	  std::cout << "in case No." << i << std::endl;
	  std::cout << "|__case's No." << j << std::endl;
	  if(p == bblocks.size() - 1)
	    break;
	  auto con = new ast::Binary(OP_EQUAL, object, situations[i]->match_list[j]);
	  BasicBlock* bnext = BasicBlock::Create(MyContext, "next", context.currentFunction);
	  llvm::BranchInst::Create(bblocks[p],bnext,con->codeGen(context),context.currentBlock());
	  context.pushBlock(bnext);
	}
    }
    
    auto con = new ast::Binary(OP_EQUAL, object, situations[i]->match_list[j]);
    auto ret= llvm::BranchInst::Create(bblocks[p],bexit,con->CodeGen(context),context.currentBlock());
    
    p = 0;
    for (i = 0;i < situations.size();i++, p++){ 
	for(j = 0; j < situations[i]->match_list.size(); j++, p++){
	  context.pushBlock(bblocks[p]);
	  situations[i]->solution->codeGen(context);
	  llvm::BranchInst::Create(bexit, context.currentBlock());
	  std::cout << "in case No." << i << std::endl;
	  std::cout << "|__case's No." << j << std::endl;
	  std::cout << "finished" << std::endl;
	  context.popBlock(); 
	}
    }
    
    context.pushBlock(bexit);

    return ret;
}

llvm::Value* ForStm::codeGen(CodeGenContext& context){
  
}

llvm::Value* WhileStm::codeGen(CodeGenContext& context){
  
}

llvm::Value* RepeatStm::codeGen(CodeGenContext& context){
  
}

llvm::Value* GotoStm::codeGen(CodeGenContext& context){
  
}

llvm::Value* UnaryExp::codeGen(CodeGenContext& context){
  
}

llvm::Value* BinaryExp::codeGen(CodeGenContext& context){
  llvm::Value* op1_val = operand1->codeGen(context);
  llvm::Value* op2_val = operand2->codeGen(context);
  
  if(op1_val->getType()->isDoubleTy() || op2_val->getType()->isDoubleTy()){
    switch(op_code){
      //arithmetic
      case OP_ADD: return llvm::BinaryOperator::Create(llvm::Instruction::FAdd, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_MINUS: return llvm::BinaryOperator::Create(llvm::Instruction::FSub, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_MULTI: return llvm::BinaryOperator::Create(llvm::Instruction::FMul, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_RDIV: return llvm::BinaryOperator::Create(llvm::Instruction::FDiv, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_DDIV: return llvm::BinaryOperator::Create(llvm::Instruction::SDiv, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_MOD: return llvm::BinaryOperator::Create(llvm::Instruction::SRem, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_AND: return llvm::BinaryOperator::Create(llvm::Instruction::And, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_OR: return llvm::BinaryOperator::Create(llvm::Instruction::Or, op1_val, op2_val, "", context.currentBlock()); break;
      //logical
      case OP_SMALL: return llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SLT, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_LARGE: return llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SGT, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_SMALL_EQUAL: return llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SGE, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_LARGE_EQUAL: return llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SLE, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_EQUAL: return llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_EQ, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_NOT_EQUAL: llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_NE, op1_val, op2_val, "", context.currentBlock()); break;
      default: return nullptr; //not know what to do
    }
  }
  else{
    switch(op_code){
      //arithmetic
      case OP_ADD: return llvm::BinaryOperator::Create(llvm::Instruction::Add, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_MINUS: return llvm::BinaryOperator::Create(llvm::Instruction::Sub, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_MULTI: return llvm::BinaryOperator::Create(llvm::Instruction::Mul, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_RDIV: return llvm::BinaryOperator::Create(llvm::Instruction::UDiv, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_DDIV: return llvm::BinaryOperator::Create(llvm::Instruction::SDiv, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_MOD: return llvm::BinaryOperator::Create(llvm::Instruction::SRem, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_AND: return llvm::BinaryOperator::Create(llvm::Instruction::And, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_OR: return llvm::BinaryOperator::Create(llvm::Instruction::Or, op1_val, op2_val, "", context.currentBlock()); break;
      //logical
      case OP_SMALL: return llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SLT, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_LARGE: return llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SGT, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_SMALL_EQUAL: return llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SGE, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_LARGE_EQUAL: return llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SLE, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_EQUAL: return llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_EQ, op1_val, op2_val, "", context.currentBlock()); break;
      case OP_NOT_EQUAL: llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_NE, op1_val, op2_val, "", context.currentBlock()); break;
      default: return nullptr; //not know what to do
    }
  }
}

llvm::Value* CallExp::codeGen(CodeGenContext& context){
  
}

llvm::Value* ConstantExp::codeGen(CodeGenContext& context){
  
}

llvm::Value* VariableExp::codeGen(CodeGenContext& context){
  
}

llvm::Value* MemoryExp::codeGen(CodeGenContext& context){
  
}

llvm::Value* ast::Value::codeGen(CodeGenContext& context){
      switch(base_type){
	case TY_INTEGER: return llvm::ConstantInt::get(llvm::Type::getInt32Ty(MyContext), val.integer_value, true);    break;
	case TY_REAL: return llvm::ConstantFP::get(MyContext, llvm::APFloat(val.real_value));    break;
	case TY_CHAR: return llvm::ConstantInt::get(llvm::Type::getInt8Ty(MyContext), val.char_value, true);     break;
	case TY_BOOLEAN: return llvm::ConstantInt::get(llvm::Type::getInt1Ty(MyContext), val.boolean_value, true);     break;
	default: return nullptr;
	//don't know yet
      }
}