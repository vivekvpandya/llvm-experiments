/** Very simple Obfuscation of constant Zero 
* 
* This pass replaces constant 0 with X ^ X where X is an integer visible register
*
**/

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"


using namespace llvm;

namespace {
class ObfuscatingZero : public BasicBlockPass {
public:
	static char ID;
	ObfuscatingZero() : BasicBlockPass(ID)
	{}
	bool runOnBasicBlock(BasicBlock &BB) override {
		bool modified = false;
		bool insHasZero = false;
		for(BasicBlock::iterator ii = BB.begin(), ie = BB.end(); ii !=ie ; ++ii){
			for(User::op_iterator opI = ii->op_begin(), opE = ii->op_end(); opI != opE ; ++opI){
						if(ConstantInt * ci = dyn_cast<ConstantInt>(*opI)){
							if(ci->isZero()){
							insHasZero = true;
							IRBuilder<> Builder(ii);
							Value *X = Builder.CreateAlloca(ci->getType());
							X->dump();
							Value *Store = Builder.CreateStore(ConstantInt::get(ci->getType(), 2),X);
							Store->dump();
							Value *Load = Builder.CreateLoad(Builder.getInt32Ty(),X);
							Load->dump();
							Value *Xor = Builder.CreateXor(Load,Load);
							*opI = Xor;
							modified = true;
							}

						}	
					}
			if(insHasZero){
			insHasZero = false;
			errs() << "The following instrunction has 0 constant :\n";
			ii->dump();
			errs() << "\n";
			}
		}
		return modified;
	}
};
}

char ObfuscatingZero::ID = 0;
static RegisterPass<ObfuscatingZero> X("obfuscatZero", "Obfuscating Zero constant",false,false);