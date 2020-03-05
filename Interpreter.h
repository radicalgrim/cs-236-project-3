#pragma once
#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
private:
	DatalogProgram program;
	Database database;
	Relation relationTemp;
public:
	Interpreter();
	Interpreter(DatalogProgram dp);
	void PrintInterpreter();
};
