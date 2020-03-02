#include "Parameter.h"

void Parameter::MakeExpression() {
/*string str = "";
	
	if (t == ADD) {
		str = " + ";
	}
	else (t == MULTIPLY) {
		str = " * ";
	}
	*/
}

Parameter::Parameter() {
	expression = "";
}

Parameter::Parameter(string exp) {
	expression = exp;
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
