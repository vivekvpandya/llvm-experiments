#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/User.h"
#include "llvm/IR/Value.h"
#include "llvm/Support/raw_ostream.h"
#include "instrMap.h"


using namespace llvm;

namespace{

	class OptLoads : public FunctionPass {
	private:
		InstrMap *instrMap; 
	public:
		static char ID;
		static int uniqInstrCount;
		OptLoads() : FunctionPass(ID){
			instrMap = new InstrMap();
		}
		bool runOnFunction(Function &F) override {
			createInstructionMap(F);
			return optimizeLoads(F);  
		}

		void createInstructionMap(Function &F){
			int tempCode;
			errs() << "OptLoads Pass Creating InstructionMap : ";
			errs().write_escaped(F.getName()) << "\n";
			for(Function::iterator funI = F.begin(), funE = F.end(); funI != funE; ++funI) {
				errs() << "Basic block ( name = " << (*funI).getName() << ") has " << funI->size() << " instructions.\n";
				for(BasicBlock::iterator ii = funI->begin(), ie = funI->end(); ii != ie; ++ii){
					tempCode = instrMap->isAlreadyInserted(ii->getOpcodeName());
					if( tempCode == -1){
						tempCode = uniqInstrCount++;
						instrMap->addInstr(ii->getOpcodeName(),tempCode);
					}
					errs() << "%"<<tempCode <<" : " <<ii->getOpcodeName()<<" " ;
					for(User::value_op_iterator opI = ii->value_op_begin(), opE = ii->value_op_end(); opI != opE ; ++opI){
						if(isa<Instruction>(*opI)){
							errs() << "%"<<instrMap->isAlreadyInserted(cast<Instruction>(*opI)->getOpcodeName()) << " ";
						}
						else if((*opI)->hasName() ){
							errs() << (*opI)->getName() << " ";
						}
						else{
							errs() << "XXX" << " ";
						}
						
					}
					errs() << "\n";
				}
				
			}
		}
		bool optimizeLoads(Function &F){
			bool returnVal =  false;
			int tempCode;
			errs() << "OptLoads Pass Optimizing loads : \n";
			
			for(Function::iterator funI = F.begin(), funE = F.end(); funI != funE; ++funI) {
				
				for(BasicBlock::iterator ii = funI->begin(), ie = funI->end(); ii != ie; ++ii){
					if(isa<StoreInst>(ii))
					{	StoreInst *stIn = cast<StoreInst>(ii);
						Value *v = stIn->getOperand(0);
						if(isa<ConstantInt>(v)){
							errs() << cast<ConstantInt>(*v).getValue();

							BasicBlock::iterator nextI = ++ii;
							if(isa<LoadInst>(nextI))
							{
								if(stIn->getOperand(1) == nextI->getOperand(0)){
									errs()<<"This is unnecessary load";
									ii->replaceAllUsesWith(v);
									returnVal = true;
								}

							}
						}
							
						
					}
				}
				
			}
			return returnVal;
		}
		void getAnalysisUsage(AnalysisUsage &Info) {

		}

	};
}


char OptLoads::ID = 0;
int OptLoads::uniqInstrCount = 1;
static RegisterPass<OptLoads> X("optLoads", "optimize unnecessary loads",false,false);