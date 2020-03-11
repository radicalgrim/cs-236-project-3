#pragma once
#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
private:
	DatalogProgram program;
	Database database;
	Relation relationTemp;
	Scheme schemeTemp;
	Tuple tupleTemp;
	void SchemeInterpreter();
	void FactInterpreter();
public:
	Interpreter();
	Interpreter(DatalogProgram dp);
	void PrintInterpreter();
};
