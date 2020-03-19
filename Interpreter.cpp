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
		//cout << "schemes in the database:" << endl;
		//for (size_t j = 0; j < program.GetSchemeList()[i].GetParameterList().size(); j++) {
		//	cout << endl << database.GetRelation(program.GetSchemeList()[i].GetName()).GetScheme().GetAttribute(j) << endl;
		//}
	}
}


//void Interpreter::FactInterpreter() {
//	for (size_t i = 0; i < program.GetFactList().size(); i++) {
//		relationTemp = database.GetRelation(program.GetFactList()[i].GetName());
//		tupleTemp = Tuple();
//		cout << "What's going into the tupletemp:" << endl;
//		for (size_t j = 0; j < program.GetFactList()[i].GetParameterList().size(); j++) {
//			tupleTemp.AddValue(program.GetFactList()[i].GetParameterList()[j].GetExpression());
//		}
//		for (size_t j = 0; j < program.GetFactList()[i].GetParameterList().size(); j++) {
//			cout << tupleTemp.GetValue(j) << endl;
//		}
//		relationTemp.AddTuple(tupleTemp);
//		database.SetRelation(relationTemp.GetName(), relationTemp);
//	}
//	
//}


void Interpreter::FactInterpreter() {
	for (size_t i = 0; i < program.GetFactList().size(); i++) {
		tupleTemp = Tuple();
		//cout << "What's going into the tupletemp:" << endl;
		for (size_t j = 0; j < program.GetFactList()[i].GetParameterList().size(); j++) {
			tupleTemp.AddValue(program.GetFactList()[i].GetParameterList()[j].GetExpression());
		}
		//for (size_t j = 0; j < program.GetFactList()[i].GetParameterList().size(); j++) {
		//	cout << tupleTemp.GetValue(j) << endl;
		//}
		database.GetRelation(program.GetFactList()[i].GetName()).AddTuple(tupleTemp);
	}

}


Relation Interpreter::EvaluateQuery(Predicate predicate) {
	map<string, int> variableTracker;
	relationTemp = database.GetRelation(predicate.GetName());

	for (size_t i = 0; i < predicate.GetParameterList().size(); i++) {
		string expression = predicate.GetParameterList()[i].GetExpression();
		
		if (predicate.GetParameterList()[i].GetConstant()) {
			relationTemp = SelectSpecificValue(i, expression);
		}
		else {
			if (variableTracker.count(expression) > 0) {
				relationTemp = SelectMatchingColumns(i, variableTracker.at(expression));
			}
			else {
				variableTracker.insert(pair<string, int>(expression, i));
			}
		}
	}

	vector<int> columnList;
	for (auto it : variableTracker) {
		columnList.push_back(it.second);
	}
	relationTemp = Project(columnList);

	vector<string> nameList;
	for (auto it : variableTracker) {
		nameList.push_back(it.first);
	}
	relationTemp = Rename(nameList);

	return relationTemp;
}


Relation Interpreter::SelectSpecificValue(int index, string value) {
	Relation newRelation = Relation(relationTemp.GetName(), relationTemp.GetScheme());
	for (auto it : relationTemp.GetTupleSet()) {
		if (it.GetValue(index) == value) {
			newRelation.AddTuple(it);
		}
	}
	return newRelation;
}


Relation Interpreter::SelectMatchingColumns(int index_1, int index_2) {
	Relation newRelation = Relation(relationTemp.GetName(), relationTemp.GetScheme());
	for (auto it : relationTemp.GetTupleSet()) {
		if (it.GetValue(index_1) == it.GetValue(index_2)) {
			newRelation.AddTuple(it);
		}
	}
	return newRelation;
}


Relation Interpreter::Project(vector<int> indexList) {
	Relation newRelation = Relation(relationTemp.GetName());
	Scheme newScheme = Scheme();
	Tuple newTuple = Tuple();
	for (size_t i = 0; i < indexList.size(); i++) {
		newScheme.AddAttribute(relationTemp.GetScheme().GetAttribute(indexList[i]));
	}
	newRelation.SetScheme(newScheme);
	for (auto it : relationTemp.GetTupleSet()) {
		for (size_t i = 0; i < indexList.size(); i++) {
			newTuple.AddValue(it.GetValue(i));
		}
		newRelation.AddTuple(newTuple);
	}
	return newRelation;
}


Relation Interpreter::Rename(vector<string> nameList) {
	Relation newRelation = Relation(relationTemp.GetName(), relationTemp.GetTupleSet());
	Scheme newScheme = Scheme();
	for (size_t i = 0; i < nameList.size(); i++) {
		newScheme.AddAttribute(nameList[i]);
	}
	newRelation.SetScheme(newScheme);
	return newRelation;
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

	vector<string> queryNameList;
	for (size_t i = 0; i < program.GetQueryList().size(); i++) {
		queryNameList.push_back(program.GetQueryList()[i].GetName());
	}

	database.PrintQueries(queryNameList);
}


void Interpreter::QueryInterpreter() {
	for (size_t i = 0; i < program.GetQueryList().size(); i++) {
		relationTemp = EvaluateQuery(program.GetQueryList()[i]);
		database.AddRelation(program.GetQueryList()[i].GetName(), relationTemp);
	}
}
