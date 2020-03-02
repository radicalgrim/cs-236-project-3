#pragma once
#include <string>
#include <vector>
#include "Token.h"
#include "Parameter.h"


class Predicate {
private:
	string name;
	vector<Parameter> parameterList;
	
public:
	Predicate();
	Predicate(string n);
	string toString();
	void SetName(string n);
	string GetName();
	void SetParameterList(vector<Parameter> list);
	vector<Parameter> GetParameterList();
};

