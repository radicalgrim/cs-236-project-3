#include "Tuple.h"

Tuple::Tuple() {

}

string Tuple::GetValue(int i) {
	return this->at(i);
}

void Tuple::AddValue(string v) {
	this->push_back(v);
}
