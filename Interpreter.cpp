#include "Interpreter.h"

Interpreter::Interpreter() {

}

Interpreter::Interpreter(DatalogProgram dp) {
	program = dp;
}

void Interpreter::PrintInterpreter() {
	cout << "In Print Interpreter" << endl;
	database.PrintDatabase();
}
