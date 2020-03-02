#include "Predicate.h"

Predicate::Predicate() {
	name = "";
}

Predicate::Predicate(string n) : name(n) {}

string Predicate::toString() {
	string str = "";

	str += name + "(";
	for (size_t i = 0; i < parameterList.size(); i++) {
		str += parameterList[i].GetExpression();
		if (i == parameterList.size() - 1) {
			str += ")";
		}
		else {
			str += ",";
		}
	}

	return str;
}

void Predicate::SetName(string n) {
	name = n;
}

string Predicate::GetName() {
	return name;
}

void Predicate::SetParameterList(vector<Parameter> list) {
	for (size_t i = 0; i < list.size(); i++) {
		parameterList.push_back(list[i]);
	}
}

vector<Parameter> Predicate::GetParameterList() {
	return parameterList;
}
