#include "Interpreter.h"


void Interpreter::SchemeInterpreter() {
	cout << endl << "Schemes:" << endl;
	for (size_t i = 0; i < program.GetSchemeList().size(); i++) {
		relationTemp = Relation(program.GetSchemeList()[i].GetName());
		schemeTemp = Scheme();
		cout << program.GetSchemeList()[i].GetName();
		for (size_t j = 0; j < program.GetSchemeList()[i].GetParameterList().size(); j++) {
			schemeTemp.AddAttribute(program.GetSchemeList()[i].GetParameterList()[j].GetExpression());
		}
		relationTemp.SetScheme(schemeTemp);
		database.AddRelation(relationTemp.GetName(), relationTemp);
		for (size_t j = 0; j < program.GetSchemeList()[i].GetParameterList().size(); j++) {
			cout << endl << "  " << database.GetRelation(program.GetSchemeList()[i].GetName()).GetScheme().GetAttribute(j);
		}
		cout << endl;
	}
	cout << endl;
}


void Interpreter::FactInterpreter() {
	cout << "Facts:" << endl;
	for (size_t i = 0; i < program.GetFactList().size(); i++) {
		tupleTemp = Tuple();
		cout << program.GetFactList()[i].GetName();
		for (size_t j = 0; j < program.GetFactList()[i].GetParameterList().size(); j++) {
			tupleTemp.AddValue(program.GetFactList()[i].GetParameterList()[j].GetExpression());
		}
		for (size_t j = 0; j < program.GetFactList()[i].GetParameterList().size(); j++) {
			cout << endl << "  " << tupleTemp.GetValue(j);
		}
		cout << endl;
		relationTemp = database.GetRelation(program.GetFactList()[i].GetName());
		relationTemp.AddTuple(tupleTemp);
		database.ResetRelation(relationTemp.GetName(), relationTemp);
	}
	cout << endl;
}


void Interpreter::QueryInterpreter() {
	cout << "Queries:" << endl;
	for (size_t i = 0; i < program.GetQueryList().size(); i++) {
		EvaluateQuery(program.GetQueryList()[i]);
	}
}


void Interpreter::EvaluateQuery(Predicate predicate) {
	map<string, int> variableTracker = map<string, int>();
	vector<int> columnList = vector<int>();
	vector<string> nameList = vector<string>();
	relationTemp = database.GetRelation(predicate.GetName());

	for (size_t i = 0; i < predicate.GetParameterList().size(); i++) {
		string expression = predicate.GetParameterList()[i].GetExpression();
		
		if (predicate.GetParameterList()[i].GetConstant()) {
			SelectSpecificValue(i, expression);
		}
		else {
			if (variableTracker.count(expression) > 0) {
				SelectMatchingColumns(i, variableTracker.at(expression));
			}
			else {
				variableTracker.insert(pair<string, int>(expression, i));
				columnList.push_back(i);
				nameList.push_back(expression);
			}
		}
	}

	Project(columnList);
	Rename(nameList);
	PrintQuery(predicate);
}


void Interpreter::SelectSpecificValue(int index, string value) {
	Relation newRelation = Relation(relationTemp.GetName(), relationTemp.GetScheme());
	for (auto it : relationTemp.GetTupleSet()) {
		if (it.GetValue(index) == value) {
			newRelation.AddTuple(it);
		}
	}
	relationTemp = newRelation;
}


void Interpreter::SelectMatchingColumns(int index_1, int index_2) {
	Relation newRelation = Relation(relationTemp.GetName(), relationTemp.GetScheme());
	for (auto it : relationTemp.GetTupleSet()) {
		if (it.GetValue(index_1) == it.GetValue(index_2)) {
			newRelation.AddTuple(it);
		}
	}
	relationTemp = newRelation;
}


void Interpreter::Project(vector<int> indexList) {
	Relation newRelation = Relation(relationTemp.GetName());
	Scheme newScheme = Scheme();
	for (size_t i = 0; i < indexList.size(); i++) {
		string attr = relationTemp.GetScheme().GetAttribute(indexList[i]);
		newScheme.AddAttribute(attr);
	}
	newRelation.SetScheme(newScheme);
	for (auto it : relationTemp.GetTupleSet()) {
		Tuple newTuple = Tuple();
		for (size_t i = 0; i < indexList.size(); i++) {
			string value = it.GetValue(indexList[i]);
			newTuple.AddValue(value);
		}
		newRelation.AddTuple(newTuple);
	}
	relationTemp = newRelation;
}


void Interpreter::Rename(vector<string> nameList) {
	Relation newRelation = Relation(relationTemp.GetName(), relationTemp.GetTupleSet());
	Scheme newScheme = Scheme();
	for (size_t i = 0; i < nameList.size(); i++) {
		newScheme.AddAttribute(nameList[i]);
	}
	newRelation.SetScheme(newScheme);
	relationTemp = newRelation;
}

void Interpreter::PrintQuery(Predicate predicate) {
	cout << relationTemp.GetName() << "(";
	for (size_t i = 0; i < predicate.GetParameterList().size(); i++) {
		cout << predicate.GetParameterList()[i].GetExpression();
		if (i < predicate.GetParameterList().size() - 1) {
			cout << ",";
		}
	}
	cout << ")? ";
	if (relationTemp.GetTupleSet().empty()) {
		cout << "No";
	}
	else {
		cout << "Yes(" << relationTemp.GetTupleSet().size() << ")";
	}
	cout << endl;
	relationTemp.PrintRelation();
}


Interpreter::Interpreter() {

}


Interpreter::Interpreter(DatalogProgram dp) {
	program = dp;
}

void Interpreter::Interpret() {
	SchemeInterpreter();
	FactInterpreter();
	QueryInterpreter();
}
