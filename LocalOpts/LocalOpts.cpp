// 15-745 S15 Assignment 1: LocalOpts.cpp
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

class LocalOpts : public BasicBlockPass {

public:
	static char ID;
	LocalOpts() : BasicBlockPass(ID){ }
	~LocalOpts() { }

	virtual void getAnalysisUsage(AnalysisUsage &AU) const {
    AU.setPreservesCFG(); // These local optimizations do not  modifiy the CFG
  }

  virtual bool runOnBasicBlock(BasicBlock &BB)
  {
  	for(BasicBlock::iterator i = BB.begin(), e = BB.end(); i != e ; i++)
  	{
  		if( i->isBinaryOp() )
  		{
  			switch ( i->getOpcode() )
  			{
  				case Instruction::Add:
  					outs() << i->getOperand(0)->getName() << " " << i->getOperand(1)->getName();
  				break;
  				case Instruction::Sub:
  					outs() << i->getOperand(0)->getName() << " " << i->getOperand(1)->getName();
  				break;
  				case Instruction::Mul:
  					outs() << i->getOperand(0)->getName() << " " << i->getOperand(1)->getName();
  				break;

  			}
  		}
  	}
  	return false;
  }

  virtual bool runOnFunction(Function &F)
  {
  	for (Function::iterator f = F.begin(), fe = F.end(); f != fe; ++fe) {
      runOnBasicBlock(*f);
    }
    return false;
  }

  virtual bool runOnModule(Module& M) 
  {

    for (Module::iterator MI = M.begin(), ME = M.end(); MI != ME; ++MI) {
      runOnFunction(*MI);
    }
    return false;
  }

};

char LocalOpts::ID = 0;
RegisterPass<LocalOpts> X("some-local-opts", "15745: Local Optimizations");

}