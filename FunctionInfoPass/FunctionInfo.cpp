// 15-745 S15 Assignment 1: FunctionInfo.cpp
////////////////////////////////////////////////////////////////////////////////

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Casting.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instructions.h"

#include <ostream>
#include <fstream>
#include <iostream>

using namespace llvm;

namespace {

class FunctionInfo : public ModulePass {

  void printFunctionInfo(Module& M) {
    outs() << "Module " << M.getModuleIdentifier().c_str() << "\n";
   }

public:

  static char ID;

  FunctionInfo() : ModulePass(ID) { }

  ~FunctionInfo() { }

  
  virtual void getAnalysisUsage(AnalysisUsage &AU) const {
    AU.setPreservesAll();
  }

  virtual bool runOnFunction(Function &F) {
  	StringRef function_name ;
  	bool is_var_arg = false;
  	size_t arg_count = 0;
  	size_t callsite_count = 0;
  	size_t block_count = 0;
  	size_t instruction_count = 0;
  	function_name = F.getName();
  	is_var_arg = F.isVarArg();
  	if(!F.arg_empty())
  		arg_count = F.arg_size();
  	block_count = F.size();
  	for(Function::iterator i = F.begin(), e = F.end(); i != e ; ++i)
  	{
  		instruction_count += i->size();
  	}
  	for(Function::iterator b = F.begin(), be = F.end(); b != be ; b++)
  	{
  		for(BasicBlock::iterator i = b->begin(), ie = b->end(); i != ie; i++)
  		{
  			if(CallInst *callInst = dyn_cast<CallInst>(&*i)){
  				if(callInst->getCalledFunction() == &F)
  					callsite_count++;
  			}
  		}
  	}
  	outs() << "Name,\tArgs,\tCalls,\tBlocks,\tInsns\n";
  	outs() << function_name << ",\t";
  	if(is_var_arg)
  		outs() << "*,\t";
  	else
  		outs() << arg_count << ",\t";
  	outs() << callsite_count << ",\t" << block_count << ",\t" << instruction_count << "\n";
    return false;
  }
  
  virtual bool runOnModule(Module& M) {

    for (Module::iterator MI = M.begin(), ME = M.end(); MI != ME; ++MI) {
      runOnFunction(*MI);
    }
    
     printFunctionInfo(M);
    return false;
  }

};

// LLVM uses the address of this static member to identify the pass, so the
// initialization value is unimportant.
char FunctionInfo::ID = 0;
RegisterPass<FunctionInfo> X("function-info", "15745: Function Information");

}
