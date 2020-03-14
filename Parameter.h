#pragma once
#include <string>
#include <iostream>
using namespace std;


class Parameter {
private:
	string expression;
	bool isConstant;
public:
	Parameter();
	Parameter(string exp);
	string toString();
	void SetExpression(string left, string exp, string right);
	string GetExpression();
	void SetConstant();
	bool GetConstant();
};

