#include "llvm/Bitcode/ReaderWriter.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/raw_os_ostream.h"
#include <iostream>
#include <system_error>

using namespace llvm;

static cl::opt<std::string> FileName (cl::Positional, cl::desc("Bitcode file"), cl::Required);

int main(int argc, char** argv) {

cl::ParseCommandLineOptions(argc, argv, "LLVM hello world\n");

LLVMContext context;


//std::unique_ptr<MemoryBuffer> mb;

DiagnosticHandlerFunction dhf;


ErrorOr<std::unique_ptr<MemoryBuffer>>  mb = MemoryBuffer::getFile(FileName); // here we got segmentation fault 

if (std::error_code EC = mb.getError()) {
                        std::cout<< "Could not open input file: " + EC.message();
   }


ErrorOr<Module *> moduleOrError  = parseBitcodeFile(mb.get()->getMemBufferRef() , context, dhf);

if(std::error_code() ){
std::cerr << "Error reading bitcode: " << std::error_code() << std::endl;
return -1;
}

raw_os_ostream O(std::cout);

Module * m = moduleOrError.get();

for (Module::const_iterator i = m -> getFunctionList().begin(), e = m -> getFunctionList().end(); i != e; ++i ) {
if(!i->isDeclaration()){
O << i->getName() << " has "<< i -> size() << "basic block(s).\n";



}
}


//O<<"ok";

return 0;

}
