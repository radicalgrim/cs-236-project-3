#pragma once
#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
private:
	DatalogProgram program;
	Database database;
	Database databaseQ;
	Relation relationTemp;
	Scheme schemeTemp;
	Tuple tupleTemp;
	void SchemeInterpreter();
	void FactInterpreter();
	void QueryInterpreter();
	void EvaluateQuery(Predicate predicate);
	void SelectSpecificValue(int index, string value);
	void SelectMatchingColumns(int index_1, int index_2);
	void Project(vector<int> indexList);
	void Rename(vector<string> nameList);
	void PrintQuery(Predicate predicate);
public:
	Interpreter();
	Interpreter(DatalogProgram dp);
	void Interpret();
};
