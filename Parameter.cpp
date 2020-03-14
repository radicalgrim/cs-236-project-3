#include "Parameter.h"

Parameter::Parameter() {
	expression = "";
	isConstant = false;
}

Parameter::Parameter(string exp) {
	expression = exp;
	isConstant = false;
}

string Parameter::toString() {
	string str = expression;
	return str;
}

void Parameter::SetExpression(string left, string exp, string right) {
	expression = left + exp + right;
}

string Parameter::GetExpression() {
	return expression;
}

void Parameter::SetConstant() {
	isConstant = true;
}

bool Parameter::GetConstant() {
	return isConstant;
}
