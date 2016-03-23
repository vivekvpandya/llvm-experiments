#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/User.h"
#include "llvm/IR/Value.h"
#include "llvm/Support/raw_ostream.h"
#include "instrMap.h"


using namespace llvm;


	class PrintCode : public FunctionPass {
	private:
		InstrMap *instrMap; 
	public:
		static char ID;
		static int uniqInstrCount;
		PrintCode() : FunctionPass(ID){
			instrMap = new InstrMap();
		}
		bool runOnFunction(Function &F) override {
			int tempCode;
			errs() << "PrintCode Pass: ";
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
			return false; // as this does not change bit code
		}
	};


char PrintCode::ID = 0;
int PrintCode::uniqInstrCount = 1;
static RegisterPass<PrintCode> X("printCode", "print code pass",false,false);