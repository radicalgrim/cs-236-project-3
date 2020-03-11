#include "Tuple.h"

Tuple::Tuple() {

}

string Tuple::GetValue(int i) {
	return valueList.at(i);
}

void Tuple::AddValue(string v) {
	valueList.push_back(v);
}
