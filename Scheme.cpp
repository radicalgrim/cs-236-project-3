#include "Scheme.h"

Scheme::Scheme() {

}

string Scheme::GetAttribute(int index) {
	return nameList.at(index);
}

int Scheme::GetLength() {
	return nameList.size();
}
