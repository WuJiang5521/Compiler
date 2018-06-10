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
	
	printf = createPrintf(*this);
	
	/* Push a new variable/block context */
	pushBlock(bblock);
	currentFunction = mainFunction;
	root.codeGen(*this); /* emit bytecode for the toplevel block */
	ReturnInst::Create(MyContext, currentBlock());
	popBlock();
	
	/* Print the bytecode in a human-readable format 
	   to see if our program compiled properly
	 */
	std::cout << "Code is generated.\n";
	//module->dump();

	//legacy::PassManager pm;
	//pm.add(createPrintModulePass(outs()));
	
	//pm.run(*module);
	std::error_code EC;
	llvm::raw_fd_ostream OS("LLVM_IR", EC, llvm::sys::fs::F_None);
	WriteBitcodeToFile(*module, OS);
	OS.flush();
	std::cout << "OS flushed" << std::endl;
	module->dump();
	
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

llvm::Function* createPrintf(CodeGenContext& context) {
    std::vector<llvm::Type *> printf_arg_types;
    printf_arg_types.push_back(llvm::Type::getInt8PtrTy(MyContext));
    llvm::FunctionType* printf_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(MyContext), printf_arg_types, true);
    llvm::Function* func = llvm::Function::Create(printf_type, llvm::Function::ExternalLinkage, llvm::Twine("printf"), context.module);
    func->setCallingConv(llvm::CallingConv::C);
    return func;
}

llvm::Type* ast::Type::toLLVMType(CodeGenContext& context){// 0: int 1: real 2: char 3: boolean 4: set 5: array 6: record 7~n: other type defined by user
  std::cout << "base type = " << base_type << std::endl;  
  switch(base_type){
      case TY_INTEGER: return llvm::Type::getInt32Ty(MyContext);
      case TY_REAL: return llvm::Type::getFloatTy(MyContext);
      case TY_CHAR: return llvm::Type::getInt8Ty(MyContext);
      case TY_BOOLEAN: return llvm::Type::getInt1Ty(MyContext);
      case TY_ARRAY: return llvm::ArrayType::get(this->child_type[0]->toLLVMType(context), array_end - array_start + 1);
      case TY_RECORD: {
	std::vector<llvm::Type*> members;
	LLVMContext ctx;
	for(auto child:child_type){
	    members.push_back(child->toLLVMType(context));
	}
	StructType*const llvm_S = StructType::create(MyContext, name);
	llvm_S->setBody(members);
	return llvm_S;
      }
      default: 
	CodeGenBlock* currBlock = context.currentCodeGenBlock();
	while(currBlock != nullptr){  
	  auto typetable = currBlock->typedefs;
	  if(typetable.find(name) != typetable.end())
	    return typetable[name]->toLLVMType(context);
	  currBlock = currBlock->parent;
	}
	std::cout << "undefined type name: " << name << std::endl;
	exit(0);
    }
}

int getRecordIndex(ast::Type* return_type, std::string name){
  for(int i = 0; i < return_type->child_type.size(); i++){
    if(name == return_type->child_type[i]->name)
      return i;
  }
  std::cout << "can'find name:" << name << " in the record named:" << return_type->name << std::endl;
  exit(0);
}

llvm::Value* getArrRef(BinaryExp* exp, CodeGenContext& context){
  if(exp->operand1->node_type == N_VARIABLE_EXP){
    VariableExp* _arr = static_cast<VariableExp*>(exp->operand1);
    auto arr = context.getValue(_arr->name);
    std::vector<llvm::Value*> indices(2);
    indices[0] = llvm::ConstantInt::get(MyContext, llvm::APInt(32, 0, true));
    indices[1] = exp->operand2->codeGen(context);
    return llvm::GetElementPtrInst::CreateInBounds(arr, llvm::ArrayRef<llvm::Value*>(indices),
							 "tempname", context.currentBlock());
  }
  else{
    std::cout << "wront array name type" << std::endl;
    exit(0);
  }
}

llvm::Value* Stm::codeGen(CodeGenContext& context){
  //do nothing
  return nullptr;
}

llvm::Value* Exp::codeGen(CodeGenContext& context){
  //do nothing
  return nullptr;
}

llvm::Value* Body::codeGen(CodeGenContext& context){
  for(auto sub_stm: stms){
    sub_stm->codeGen(context);
    std::cout << "one sub_stm done" << std::endl;
  }
  return nullptr;
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
  return nullptr;
}

llvm::Value* Situation::codeGen(CodeGenContext& context){
  //do nothing because CaseStm did everything
  return nullptr;
}

llvm::Value* LabelDef::codeGen(CodeGenContext& context){
  //don't know what to do
  return nullptr;
}

llvm::Value* ConstDef::codeGen(CodeGenContext& context){
  std::cout << "creating const: " << name << std::endl;
  if(value->node_type == N_CONSTANT_EXP){
    ConstantExp* _opLeft = static_cast<ConstantExp*>(value);
    auto alloc = new llvm::AllocaInst(_opLeft->return_type->toLLVMType(context), 0,  name.c_str(), context.currentBlock());
    auto store = new llvm::StoreInst(_opLeft->return_value->codeGen(context), alloc, false, context.currentBlock());
    context.insertConst(name, value);
    std::cout << "creating const done" << std::endl;
    return store;
  }
  else{
    std::cout << "Wrong left Value" << std::endl;
    exit(0);
  }
}

llvm::Value* TypeDef::codeGen(CodeGenContext& context){
  context.currentCodeGenBlock()->typedefs[name] = type;
}


//TODO array of records and other user defined types
llvm::Value* VarDef::codeGen(CodeGenContext& context){
  std::cout << "variable define: " << name << std::endl;
  llvm::Value* alloc;
  if(is_global){
    std::cout << "<global-variable>" << name << std::endl;
    if(type->array_end != 0 || type->array_start != 0 ){//is array
      std::cout << " |__is an array" << std::endl;
      auto vec = std::vector<llvm::Constant*>();
      llvm::Constant* ele_of_arr;
      switch(type->child_type[0]->base_type){
	case TY_INTEGER: ele_of_arr = llvm::ConstantInt::get(llvm::Type::getInt32Ty(MyContext), 0, true);  break;
	case TY_REAL: ele_of_arr = llvm::ConstantFP::get(llvm::Type::getFloatTy(MyContext), 0);    break;
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
					 false, llvm::GlobalValue::ExternalLinkage , llvm::ConstantFP::get(llvm::Type::getFloatTy(MyContext), 0), name);
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
    for(ast::Type *it : args_type){
	arg_types.push_back(it->toLLVMType(context)); 
    }
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
	std::cout << "variable define: " << args_name[i] << std::endl;
        llvm::Value* alloc;
        alloc = new llvm::AllocaInst(args_type[i]->toLLVMType(context), 0, args_name[i].c_str(), context.currentBlock());
	arg_value = args_values++;
        arg_value->setName(args_name[i].c_str());
        auto inst = new llvm::StoreInst(arg_value, alloc, false, block);
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
  std::cout << "Creating assignment..." << std::endl;
  if(left_value->node_type == N_BINARY_EXP){//left is an array Elemet
    BinaryExp* _op1 = static_cast<BinaryExp*>(left_value);
    if(_op1->op_code == OP_INDEX){
      llvm::Value* elementPtr = getArrRef(_op1, context);
      return new llvm::StoreInst(right_value->codeGen(context), elementPtr, false, context.currentBlock());
    }
    else{
      std::cout << "wrong left value type" << std::endl;
      exit(0);
    }
  }
  else if(left_value->node_type == N_VARIABLE_EXP){
    VariableExp* _op1 = static_cast<VariableExp*>(left_value);
    if(_op1->codeGen(context)->getType()->isArrayTy()){
      if(right_value->node_type == N_VARIABLE_EXP){
	VariableExp* _op2 = static_cast<VariableExp*>(right_value);
	if(_op2->codeGen(context)->getType()->isArrayTy()){
	  if((_op1->return_type->array_end - _op1->return_type->array_start) ==
	    (_op2->return_type->array_end - _op2->return_type->array_start)){
	    int size = _op1->return_type->array_end - _op1->return_type->array_start;
	    auto arrLeft = context.getValue(_op1->return_type->name);
	    auto arrRight = context.getValue(_op2->return_type->name);
	    std::vector<llvm::Value*> indicesLeft(2);
	    indicesLeft[0] = llvm::ConstantInt::get(MyContext, llvm::APInt(32, 0, true));
	    std::vector<llvm::Value*> indicesRight(2);
	    indicesRight[0] = llvm::ConstantInt::get(MyContext, llvm::APInt(32, 0, true));
	    llvm::Value* member_ptrLeft;
	    llvm::Value* member_ptrRight;
	    llvm::Value* temp;
	    int i;
	    for(i = 0; i < size - 1; i++){
	      indicesLeft[1] = llvm::ConstantInt::get(MyContext, llvm::APInt(32, i, true));
	      indicesRight[1] = llvm::ConstantInt::get(MyContext, llvm::APInt(32, i, true));
	      member_ptrLeft = llvm::GetElementPtrInst::CreateInBounds(arrLeft, llvm::ArrayRef<llvm::Value*>(indicesLeft),
							 "tempname", context.currentBlock());
	      member_ptrRight = llvm::GetElementPtrInst::CreateInBounds(arrRight, llvm::ArrayRef<llvm::Value*>(indicesRight),
							 "tempname", context.currentBlock());
	      temp = new llvm::LoadInst(member_ptrRight, "", false, context.currentBlock());
	      auto store = new llvm::StoreInst(temp, member_ptrLeft, false, context.currentBlock());
	    }
	    indicesLeft[1] = llvm::ConstantInt::get(MyContext, llvm::APInt(32, i, true));
	    indicesRight[1] = llvm::ConstantInt::get(MyContext, llvm::APInt(32, i, true));
	    member_ptrLeft = llvm::GetElementPtrInst::CreateInBounds(arrLeft, llvm::ArrayRef<llvm::Value*>(indicesLeft),
							 "tempname", context.currentBlock());
	    member_ptrRight = llvm::GetElementPtrInst::CreateInBounds(arrRight, llvm::ArrayRef<llvm::Value*>(indicesRight),
							 "tempname", context.currentBlock());
	    temp = new llvm::LoadInst(member_ptrRight, "", false, context.currentBlock());
	    return new llvm::StoreInst(temp, member_ptrLeft, false, context.currentBlock());
	  }
	  else{
	    std::cout << "size mismatch between arrays in assignment operation" << std::endl;
	  }
	}
      }
      std::cout << "leftVale is a array type but the rightValue is not" << std::endl;
    }
    else{
//       if(context.currentCodeGenBlock()->is_formal_param.find(_op1->name) != (context.currentCodeGenBlock()->is_formal_param.end())){
// 	llvm::Value* _ld1 = new llvm::LoadInst(context.getValue(_op1->name), "", false, context.currentBlock());
// 	return new llvm::StoreInst(right_value->codeGen(context), _ld1, false, context.currentBlock());
//       }
//       else{
// 	llvm::Value* right = right_value->codeGen(context);
	return new llvm::StoreInst(right_value->codeGen(context), context.getValue(_op1->name), false, context.currentBlock());
//       }
    }
  }
}

llvm::Value* CallStm::codeGen(CodeGenContext& context){
  if(name == "write" || name == "writeln"){
    bool writeln = false;
    if(name == "writeln")
      writeln = true;
    std::string printf_format;
    std::vector<llvm::Value *> printf_args;

    for(auto arg :args) {
        llvm::Value* arg_val = arg->codeGen(context);
        if (arg_val->getType() == llvm::Type::getInt32Ty(MyContext)) {
            printf_format += "%d";
            std::cout << "SysFuncCall write variable previous name" << arg_val->getName().str() << std::endl;
            printf_args.push_back(arg_val);
        } else if (arg_val->getType()->isFloatTy()) {
            printf_format += "%f";
            printf_args.push_back(arg_val);
        } else if (arg_val->getType() == llvm::Type::getInt8PtrTy(MyContext)) {
            std::cout << "string print is not supported" << std::endl;
        }
    }
    
    if (writeln)
        printf_format += "\n";
    
    std::cout << "Desierdsaefad Format: " << printf_format << std::endl;
    
    llvm::Constant* printf_format_const = llvm::ConstantDataArray::getString(MyContext, printf_format.c_str());

    llvm::GlobalVariable* format_string_var = new llvm::GlobalVariable(*context.module,llvm::ArrayType::get(llvm::IntegerType::get(MyContext, 8),strlen(printf_format.c_str())+ 1),true, llvm::GlobalValue::PrivateLinkage, printf_format_const, ".str");
    
    llvm::Constant* zero = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(MyContext));
    std::vector<llvm::Constant *> indices;
    indices.push_back(zero); 
    indices.push_back(zero);
    
    llvm::Constant* var_ref = llvm::ConstantExpr::getGetElementPtr(llvm::ArrayType::get(llvm::IntegerType::get(MyContext, 8),strlen(printf_format.c_str())+ 1),format_string_var,indices);
    
    printf_args.insert(printf_args.begin(), var_ref);
    auto call = llvm::CallInst::Create(context.printf, llvm::makeArrayRef(printf_args), "", context.currentBlock());
    //llvm::ReturnInst::Create(llvm::getGlobalContext(), block);
    std::cout << "write or writeln called" << std::endl;
    //context.popBlock();
    return call;
  }
  
  
  auto function = context.module->getFunction(name.c_str());
  if (function == nullptr){
     std::cout << "calling function named " << name << " but not defined" << std::endl;
     exit(0);
  }
  auto func_args_values = function->arg_begin();
  llvm::Value* func_arg_value;
  std::vector<llvm::Value*> _args;
  for(auto arg :args) {
    func_arg_value = func_args_values++;
    if(func_arg_value->getType()->isPointerTy()){
      if(arg->node_type == N_VARIABLE_EXP){
	VariableExp* _node = static_cast<VariableExp*>(arg);
	_args.push_back(context.getValue(_node->name));
      }
      else if(arg->node_type == N_BINARY_EXP){
	BinaryExp* _node = static_cast<BinaryExp*>(arg);
	if(_node->op_code == OP_DOT){
	  if(_node->operand2->node_type == N_VARIABLE_EXP){
	    VariableExp* _op2 = static_cast<VariableExp*>(_node->operand2);
	    //get index in the record
	    int index = getRecordIndex(_node->operand1->return_type, _op2->name);
	    llvm::Value* member_index = llvm::ConstantInt::get(MyContext, llvm::APInt(32, index, true));//create member_index
	    std::vector<llvm::Value*> indices(2);
	    indices[0] = llvm::ConstantInt::get(MyContext, llvm::APInt(32, 0, true));
	    indices[1] = member_index;
	    llvm::Value* member_ptr;
	    member_ptr = llvm::GetElementPtrInst::Create(_node->operand1->return_type->toLLVMType(context), context.getValue(_op2->name),
						   indices, "", context.currentBlock());
	    _args.push_back(member_ptr);
	  }
	  else{
	    std::cout << "operand2 of Dot operation is not a VariableExp Type" << std::endl;
	  }
	}
	else if(_node->op_code == OP_INDEX){
	  if(_node->operand1->node_type == N_VARIABLE_EXP){
	    VariableExp* _op1 = static_cast<VariableExp*>(_node->operand1);
	    auto arr = context.getValue(_op1->name);
	    std::vector<llvm::Value*> indices(2);
	    indices[0] = llvm::ConstantInt::get(MyContext, llvm::APInt(32, 0, true));
	    indices[1] = _node->operand2->codeGen(context);
	    llvm::Value* member_ptr;
	    member_ptr = llvm::GetElementPtrInst::CreateInBounds(arr, llvm::ArrayRef<llvm::Value*>(indices),
							 "tempname", context.currentBlock());
	    _args.push_back(member_ptr);
	 }
	  else{
	    std::cout << "Array's Ref is not an array type variable" << std::endl;
	    exit(0);
	  }
	}
      }
      else{
	std::cout << "wrong left value type" << std::endl;
      }
    }
    else{
      _args.push_back(arg->codeGen(context));
    }
  }
  auto call = llvm::CallInst::Create(function, llvm::makeArrayRef(_args), "", context.currentBlock());
  std::cout << "Created method call: " << name << std::endl;
  return call;
}

llvm::Value* LabelStm::codeGen(CodeGenContext& context){
  context.labelBlock[label] = BasicBlock::Create(MyContext, "label", context.currentFunction, 0);
  llvm::BranchInst::Create(context.labelBlock[label], context.currentBlock());
  context.pushBlock(context.labelBlock[label]);
  return nullptr;
}

llvm::Value* IfStm::codeGen(CodeGenContext& context){
  std::cout << "Creating IFStm" << std::endl;
  llvm::Value* test = condition->codeGen(context);
  std::cout << "condition generated" << std::endl;
  BasicBlock *btrue = BasicBlock::Create(MyContext, "thenStmt", context.currentFunction);
  BasicBlock *bfalse = BasicBlock::Create(MyContext, "elseStmt", context.currentFunction);
  BasicBlock *bmerge = BasicBlock::Create(MyContext, "mergeStmt", context.currentFunction);    
  auto ret = llvm::BranchInst::Create(btrue,bfalse,test,context.currentBlock());

  context.pushBlock(btrue);
  true_do->codeGen(context);
  std::cout << "true block generated" << std::endl;
  llvm::BranchInst::Create(bmerge,context.currentBlock());
  context.popBlock();
  context.pushBlock(bfalse);
  if (false_do != nullptr){
      false_do->codeGen(context);
      std::cout << "false block generated" << std::endl;
  }
  llvm::BranchInst::Create(bmerge,context.currentBlock());
  context.popBlock();
  context.pushBlock(bmerge);
  
  return ret;
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
	  auto con = new ast::BinaryExp(OP_EQUAL, object, situations[i]->match_list[j]);
	  BasicBlock* bnext = BasicBlock::Create(MyContext, "next", context.currentFunction);
	  llvm::BranchInst::Create(bblocks[p],bnext,con->codeGen(context),context.currentBlock());
	  context.pushBlock(bnext);
	}
    }
    
    auto con = new ast::BinaryExp(OP_EQUAL, object, situations[i]->match_list[j]);
    auto ret= llvm::BranchInst::Create(bblocks[p],bexit,con->codeGen(context),context.currentBlock());
    
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
    BasicBlock *sloop = BasicBlock::Create(MyContext, "startloop", context.currentFunction);
    BasicBlock *bloop = BasicBlock::Create(MyContext, "loopStmt", context.currentFunction);
    BasicBlock *bexit = BasicBlock::Create(MyContext, "eixtStmt", context.currentFunction);    
//  initial for   
    ast::VariableExp* loopVar = new ast::VariableExp(iter);
    loopVar->return_type = ast::findVar(iter, this);
    loopVar->name = iter;
    ast::AssignStm* initial = new AssignStm(loopVar,start);
    initial->codeGen(context);
    llvm::BranchInst::Create(sloop,context.currentBlock());
//  for test
    context.pushBlock(sloop);
    ast::BinaryExp* compare = new BinaryExp(OP_EQUAL, loopVar, end);
    llvm::Value* test = compare->codeGen(context);
    llvm::Instruction *ret = llvm::BranchInst::Create(bexit,bloop,test,context.currentBlock());
    context.popBlock();

    context.pushBlock(bloop);
    loop->codeGen(context);
//update
    BinaryExp* update;
    ast::Value *temp_value = new ast::Value();
    temp_value->base_type = TY_INTEGER;
    temp_value->val.integer_value = 1;
    ConstantExp * int1 = new ConstantExp(temp_value);
    if (step == 1) {
        update = new BinaryExp(OP_ADD, loopVar, int1);
    }
    else{
        update = new BinaryExp(OP_MINUS, loopVar, int1);
    }
    auto updateStmt = new AssignStm(loopVar,update);
    updateStmt->codeGen(context);
    llvm::BranchInst::Create(sloop,context.currentBlock());
    context.popBlock();

    context.pushBlock(bexit);
    loop->codeGen(context);
    delete initial;
    delete compare;
    delete int1;
    delete update;
    delete updateStmt;
    return ret;
}

llvm::Value* WhileStm::codeGen(CodeGenContext& context){
  BasicBlock *sloop = BasicBlock::Create(MyContext, "startloop", context.currentFunction);
  BasicBlock *bloop = BasicBlock::Create(MyContext, "loopStmt", context.currentFunction);
  BasicBlock *bexit = BasicBlock::Create(MyContext, "eixtStmt", context.currentFunction);    
  llvm::BranchInst::Create(sloop,context.currentBlock());
  context.pushBlock(sloop);
  llvm::Value* test = condition->codeGen( context );
  llvm::Instruction *ret = llvm::BranchInst::Create(bloop,bexit,test,context.currentBlock());
  context.popBlock();

  context.pushBlock(bloop);
  loop->codeGen(context);
  llvm::BranchInst::Create(sloop,context.currentBlock());
  context.popBlock();

  context.pushBlock(bexit);

  return ret;
}

llvm::Value* RepeatStm::codeGen(CodeGenContext& context){
  BasicBlock *bloop = BasicBlock::Create(MyContext, "loopStmt", context.currentFunction);
  BasicBlock *bexit = BasicBlock::Create(MyContext, "eixtStmt", context.currentFunction);    
  llvm::BranchInst::Create(bloop,context.currentBlock());

  context.pushBlock(bloop);
  loop->codeGen(context);
  llvm::Value* test = condition->codeGen( context );
  llvm::Instruction *ret = llvm::BranchInst::Create(bexit,bloop,test,context.currentBlock());
  context.popBlock();

  context.pushBlock(bexit);

  return ret;
}

llvm::Value* GotoStm::codeGen(CodeGenContext& context){
  //llvm::Value* test = (new )
  BasicBlock* bafter = BasicBlock::Create(MyContext, "aftergoto", context.currentFunction, 0);
  auto ret = llvm::BranchInst::Create(context.labelBlock[label], context.currentBlock());
  context.pushBlock(bafter);
  return ret;
}

llvm::Value* UnaryExp::codeGen(CodeGenContext& context){
  switch(op_code){
    case OP_NOT:
      return llvm::BinaryOperator::Create(llvm::Instruction::Xor, operand->codeGen(context), 
					  llvm::ConstantInt::get(llvm::Type::getInt1Ty(MyContext), 1, true), "", context.currentBlock());
      break;
    case OP_OPPO:
      if(operand->return_type->base_type == TY_INTEGER){
	return llvm::BinaryOperator::Create(llvm::Instruction::Sub,
					    llvm::ConstantInt::get(llvm::Type::getInt32Ty(MyContext), 0, true),
					    operand->codeGen(context),
					    "",
					    context.currentBlock());
      }
      else if(operand->return_type->base_type == TY_REAL){
	return llvm::BinaryOperator::Create(llvm::Instruction::FSub,
					    llvm::ConstantFP::get(MyContext, llvm::APFloat(0.)),
					    operand->codeGen(context),
					    "",
					    context.currentBlock());
      }
      break;
    case OP_ABS:
       if(operand->return_type->base_type == TY_INTEGER){
	  auto test = llvm::CmpInst::Create(llvm::Instruction::ICmp,
				       llvm::CmpInst::ICMP_SGT,
				       llvm::ConstantInt::get(llvm::Type::getInt32Ty(MyContext), 0, true),
				       operand->codeGen(context), "", context.currentBlock());
	  BasicBlock *btrue = BasicBlock::Create(MyContext, "thenStmt", context.currentFunction);
	  BasicBlock *bfalse = BasicBlock::Create(MyContext, "elseStmt", context.currentFunction);
	  BasicBlock *bmerge = BasicBlock::Create(MyContext, "mergeStmt", context.currentFunction);    
	  auto ret = llvm::BranchInst::Create(btrue,bfalse,test,context.currentBlock());

	  context.pushBlock(btrue);
	  llvm::BinaryOperator::Create(llvm::Instruction::Sub,
				       llvm::ConstantInt::get(llvm::Type::getInt32Ty(MyContext), 0, true),
				       operand->codeGen(context),
				       "",
				       context.currentBlock());
	  llvm::BranchInst::Create(bmerge,context.currentBlock());
	  context.popBlock();
	  context.pushBlock(bfalse);
	  operand->codeGen(context);
	  llvm::BranchInst::Create(bmerge,context.currentBlock());
	  context.popBlock();
	  context.pushBlock(bmerge);
	  return ret;
      }
      else if(operand->return_type->base_type == TY_REAL){
	auto test = llvm::CmpInst::Create(llvm::Instruction::ICmp,
				       llvm::CmpInst::ICMP_SGT,
				       llvm::ConstantFP::get(MyContext, llvm::APFloat(0.)),
				       operand->codeGen(context), "", context.currentBlock());
	  BasicBlock *btrue = BasicBlock::Create(MyContext, "thenStmt", context.currentFunction);
	  BasicBlock *bfalse = BasicBlock::Create(MyContext, "elseStmt", context.currentFunction);
	  BasicBlock *bmerge = BasicBlock::Create(MyContext, "mergeStmt", context.currentFunction);    
	  auto ret = llvm::BranchInst::Create(btrue,bfalse,test,context.currentBlock());

	  context.pushBlock(btrue);
	  llvm::BinaryOperator::Create(llvm::Instruction::FSub,
				       llvm::ConstantFP::get(MyContext, llvm::APFloat(0.)),
				       operand->codeGen(context),
				       "",
				       context.currentBlock());
	  llvm::BranchInst::Create(bmerge,context.currentBlock());
	  context.popBlock();
	  context.pushBlock(bfalse);
	  operand->codeGen(context);
	  llvm::BranchInst::Create(bmerge,context.currentBlock());
	  context.popBlock();
	  context.pushBlock(bmerge);
	  return ret;
      }
      break;
    case OP_PRED:
      return llvm::BinaryOperator::Create(llvm::Instruction::Sub, 
				   operand->codeGen(context),
				   llvm::ConstantInt::get(llvm::Type::getInt8Ty(MyContext), 1, true),
				   "",
				   context.currentBlock());
      break;;
    case OP_SUCC:
      return llvm::BinaryOperator::Create(llvm::Instruction::Add, 
				   operand->codeGen(context),
				   llvm::ConstantInt::get(llvm::Type::getInt8Ty(MyContext), 1, true),
				   "",
				   context.currentBlock());
      break;
    case OP_ODD:
      return llvm::BinaryOperator::Create(llvm::Instruction::And, 
					  llvm::ConstantInt::get(llvm::Type::getInt32Ty(MyContext), 0, true),
					  operand->codeGen(context),
					  "",
					  context.currentBlock());
    case OP_CHR:
      return CastInst::CreateIntegerCast(operand->codeGen(context),
					 llvm::Type::getInt8Ty(MyContext),
					 true,
					 "",
					 context.currentBlock());
    case OP_ORD:
      return CastInst::CreateIntegerCast(operand->codeGen(context),
					 llvm::Type::getInt32Ty(MyContext),
					 true,
					 "",
					 context.currentBlock());
  }
}

llvm::Value* BinaryExp::codeGen(CodeGenContext& context){
  //for dot(record)
  if(op_code == OP_DOT){
    if(operand2->node_type == N_VARIABLE_EXP){
      VariableExp* _op2 = static_cast<VariableExp*>(operand2);
      //get index in the record
      int index = getRecordIndex(operand1->return_type, _op2->name);
      llvm::Value* member_index = llvm::ConstantInt::get(MyContext, llvm::APInt(32, index, true));//create member_index
      std::vector<llvm::Value*> indices(2);
      indices[0] = llvm::ConstantInt::get(MyContext, llvm::APInt(32, 0, true));
      indices[1] = member_index;
      llvm::Value* member_ptr;
      member_ptr = llvm::GetElementPtrInst::Create(operand1->return_type->toLLVMType(context), context.getValue(_op2->name),
						   indices, "", context.currentBlock());
      return new llvm::LoadInst(member_ptr, "", false, context.currentBlock());
    }
    else{
      std::cout << "operand2 of Dot operation is not a VariableExp Type" << std::endl;
    }
  }
  else if(op_code == OP_INDEX){
    if(operand1->node_type == N_VARIABLE_EXP){
      VariableExp* _op1 = static_cast<VariableExp*>(operand1);
      auto arr = context.getValue(_op1->name);
      std::vector<llvm::Value*> indices(2);
      indices[0] = llvm::ConstantInt::get(MyContext, llvm::APInt(32, 0, true));
      indices[1] = operand2->codeGen(context);
      llvm::Value* member_ptr;
      member_ptr = llvm::GetElementPtrInst::CreateInBounds(arr, llvm::ArrayRef<llvm::Value*>(indices),
							 "tempname", context.currentBlock());
      return new llvm::LoadInst(member_ptr, "", false, context.currentBlock());
    }
    else{
      std::cout << "Array's Ref is not an array type variable" << std::endl;
      exit(0);
    }
  }
  
  //for normal
  llvm::Value* op1_val = operand1->codeGen(context);
  llvm::Value* op2_val = operand2->codeGen(context);
  
  if(op1_val->getType()->isFloatTy() || op2_val->getType()->isFloatTy()){
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
      case OP_NOT_EQUAL: return llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_NE, op1_val, op2_val, "", context.currentBlock()); break; 
      default: 
	std::cout << "unknown type of op_code:" << op_code << std::endl; //not know what to do
	exit(0);
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
      case OP_NOT_EQUAL: return llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_NE, op1_val, op2_val, "", context.currentBlock()); break;
      default: 
	std::cout << "unknown type of op_code:" << op_code << std::endl; //not know what to do
	exit(0);
    }
  }
}

llvm::Value* CallExp::codeGen(CodeGenContext& context){
  std::cout << "creating calling " << std::endl;
  auto function = context.module->getFunction(name.c_str());
  if (function == nullptr){
     std::cout << "calling function named " << name << " but not defined" << std::endl;
     exit(0);
  }
  auto func_args_values = function->arg_begin();
  llvm::Value* func_arg_value;
  std::vector<llvm::Value*> _args;
  for(auto arg :args) {
    func_arg_value = func_args_values++;
    if(func_arg_value->getType()->isPointerTy()){
      if(arg->node_type == N_VARIABLE_EXP){
	VariableExp* _node = static_cast<VariableExp*>(arg);
	_args.push_back(context.getValue(_node->name));
      }
      else if(arg->node_type == N_BINARY_EXP){
	BinaryExp* _node = static_cast<BinaryExp*>(arg);
	if(_node->op_code == OP_DOT){
	  if(_node->operand2->node_type == N_VARIABLE_EXP){
	    VariableExp* _op2 = static_cast<VariableExp*>(_node->operand2);
	    //get index in the record
	    int index = getRecordIndex(_node->operand1->return_type, _op2->name);
	    llvm::Value* member_index = llvm::ConstantInt::get(MyContext, llvm::APInt(32, index, true));//create member_index
	    std::vector<llvm::Value*> indices(2);
	    indices[0] = llvm::ConstantInt::get(MyContext, llvm::APInt(32, 0, true));
	    indices[1] = member_index;
	    llvm::Value* member_ptr;
	    member_ptr = llvm::GetElementPtrInst::Create(_node->operand1->return_type->toLLVMType(context), context.getValue(_op2->name),
						   indices, "", context.currentBlock());
	    _args.push_back(member_ptr);
	  }
	  else{
	    std::cout << "operand2 of Dot operation is not a VariableExp Type" << std::endl;
	  }
	}
	else if(_node->op_code == OP_INDEX){
	  if(_node->operand1->node_type == N_VARIABLE_EXP){
	    VariableExp* _op1 = static_cast<VariableExp*>(_node->operand1);
	    auto arr = context.getValue(_op1->name);
	    std::vector<llvm::Value*> indices(2);
	    indices[0] = llvm::ConstantInt::get(MyContext, llvm::APInt(32, 0, true));
	    indices[1] = _node->operand2->codeGen(context);
	    llvm::Value* member_ptr;
	    member_ptr = llvm::GetElementPtrInst::CreateInBounds(arr, llvm::ArrayRef<llvm::Value*>(indices),
							 "tempname", context.currentBlock());
	    _args.push_back(member_ptr);
	 }
	  else{
	    std::cout << "Array's Ref is not an array type variable" << std::endl;
	    exit(0);
	  }
	}
      }
      else{
	std::cout << "wrong left value type" << std::endl;
      }
    }
    else{
      _args.push_back(arg->codeGen(context));
    }
  }
  auto call = llvm::CallInst::Create(function, llvm::makeArrayRef(_args), "", context.currentBlock());
  std::cout << "Created method call: " << name << std::endl;
  return call;
}

llvm::Value* ConstantExp::codeGen(CodeGenContext& context){
  return value->codeGen(context);
}

llvm::Value* VariableExp::codeGen(CodeGenContext& context){
  std::cout << "loading variable: " << name << std::endl;
//   if(context.currentCodeGenBlock()->is_formal_param.find(name) != (context.currentCodeGenBlock()->is_formal_param.end())){
//     std::cout << "found formal parameter " << name << std::endl;
//     llvm::Value* _ld1 = new llvm::LoadInst(context.getValue(name), "", false, context.currentBlock());
//     return new llvm::LoadInst(_ld1, "", false, context.currentBlock());
//   }
//   else{
    return new llvm::LoadInst(context.getValue(name), "", false, context.currentBlock());
//   }
}

llvm::Value* ast::Type::codeGen(CodeGenContext& context){
  //do nothing
  return nullptr;
}

llvm::Value* ExpList::codeGen(CodeGenContext& context){
  //do nothing
  return nullptr;
}



llvm::Value* ast::Value::codeGen(CodeGenContext& context){
      switch(base_type){
	case TY_INTEGER: return llvm::ConstantInt::get(llvm::Type::getInt32Ty(MyContext), val.integer_value, true);    break;
	case TY_REAL: return llvm::ConstantFP::get(MyContext, llvm::APFloat(val.real_value));      break;
	case TY_CHAR: return llvm::ConstantInt::get(llvm::Type::getInt8Ty(MyContext), val.char_value, true);     break;
	case TY_BOOLEAN: return llvm::ConstantInt::get(llvm::Type::getInt1Ty(MyContext), val.boolean_value, true);     break;
	default: return nullptr;
	//don't know yet
      }
}