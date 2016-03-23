#include "instrMap.h"

InstrMap::InstrMap(){
}

void InstrMap::addInstr(const char *instr, int code){
	InstrMap::instMap[instr]= code;
	
}
int InstrMap::isAlreadyInserted(const char *instr){
	if(InstrMap::instMap.find(instr) == InstrMap::instMap.end())
		return -1;
	else
		return InstrMap::instMap[instr];
}