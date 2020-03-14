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
	Relation EvaluateSingleQuery(Predicate predicate);
	Relation SelectSpecificValue(int index, string value);
	Relation SelectMatchingColumns(int index_1, int index_2);
	Relation Project(vector<int> indexList);
	Relation Rename(vector<string> nameList);
public:
	Interpreter();
	Interpreter(DatalogProgram dp);
	void PrintInterpreter();
	void EvaluateAllQueries();
};
