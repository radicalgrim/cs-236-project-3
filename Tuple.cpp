#include "Tuple.h"

Tuple::Tuple() {

}

string Tuple::GetValue(int i) {
	return valueList.at(i);
}
