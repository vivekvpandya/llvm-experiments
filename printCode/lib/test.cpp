#include <iostream>
#include "instrMap.h"

int main(){

	InstrMap *map = new InstrMap();
	map->addInstr("V",1);
	if(map->isAlreadyInserted("V"))
		std::cout << "Finds!";
	else
		std::cout << "Not Finds";

	if(map->isAlreadyInserted("D"))
		std::cout << "Finds!";
	else
		std::cout << "Not Finds";
	return 0;
}