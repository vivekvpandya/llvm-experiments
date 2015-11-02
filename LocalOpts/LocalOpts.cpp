// 15-745 S15 Assignment 1: LocalOpts.cpp
////////////////////////////////////////////////////////////////////////////////
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Casting.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"

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
  { // InstructionSimplify and BasicBlockUtil class can help here. Need to read more about them .
    for(BasicBlock::iterator i = BB.begin(), e = BB.end(); i != e ; i++)
    {
      if( i->isBinaryOp() )
      {
        Value *firsOperand = i->getOperand(0);
        if(ConstantInt *cone = dyn_cast<ConstantInt>(firsOperand))
        {  
          APInt coneval = cone->getValue();
          Value *secondOperand = i->getOperand(1);
          if(ConstantInt *ctwo = dyn_cast<ConstantInt>(secondOperand))
          { APInt ctwoval = ctwo->getValue();
            i->dump();
            outs() << "\n";
            APInt eval ;
            switch(i->getOpcode()){
              case Instruction::Add :
              eval = coneval + ctwoval;
              break;
              case Instruction::Sub :
              eval = coneval - ctwoval;
              break;
              case Instruction::Mul :
              eval = coneval * ctwoval;
              break;
            }
            outs() << eval << "\n";


          }
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