#pragma once
#include <string>
#include <iostream>
//#include "Parser.h"
using namespace std;


class Parameter {
private:
	string expression;
	void MakeExpression();
public:
	Parameter();
	Parameter(string exp);
	string toString();
	void SetExpression(string left, string exp, string right);
	string GetExpression();
};

