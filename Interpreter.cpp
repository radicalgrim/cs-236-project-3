#include "Interpreter.h"

void Interpreter::SchemeInterpreter() {
	for (size_t i = 0; i < program.GetSchemeList().size(); i++) {
		relationTemp = Relation(program.GetSchemeList()[i].GetName());
		schemeTemp = Scheme();
		for (size_t j = 0; j < program.GetSchemeList()[i].GetParameterList().size(); j++) {
			schemeTemp.AddAttribute(program.GetSchemeList()[i].GetParameterList()[j].GetExpression());
		}
		relationTemp.SetScheme(schemeTemp);
		database.AddRelation(relationTemp.GetName(), relationTemp);
	}
}

void Interpreter::FactInterpreter() {
	for (size_t i = 0; i < program.GetFactList().size(); i++) {
		relationTemp = database.GetRelation(program.GetFactList()[i].GetName());
		tupleTemp = Tuple();
		for (size_t j = 0; j < program.GetFactList()[i].GetParameterList().size(); j++) {
			tupleTemp.AddValue(program.GetFactList()[i].GetParameterList()[j].GetExpression());
		}
		database.SetRelation(relationTemp.GetName(), tupleTemp);
	}
}

Interpreter::Interpreter() {

}

Interpreter::Interpreter(DatalogProgram dp) {
	program = dp;
	SchemeInterpreter();
	FactInterpreter();
}

void Interpreter::PrintInterpreter() {
	cout << "In Print Interpreter" << endl;
	database.PrintDatabase();
}
