#ifndef INSTRMAP_H
#define INSTRMAP_H

#include <map>

class InstrMap {

private:
	std::map<const char *,int> instMap;
public:
	InstrMap();
	void addInstr(const char *, int);
	int isAlreadyInserted(const char *);

};

#endif //INSTRMAP_H