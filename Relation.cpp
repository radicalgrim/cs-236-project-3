#include "Relation.h"

Relation::Relation() {
}

Relation::Relation(string n, Scheme s) {
	name = n;
	scheme = s;
}

void Relation::AddTuple(Tuple t) {
	tupleSet.insert(t);
}

void Relation::PrintRelations() {
	for (auto& it : tupleSet) {
	}
}

void Relation::ToString(int i) {
	for (size_t j = 0; j < scheme.GetLength(); j++) {
		cout << scheme.GetAttribute(j) << "=";
	}
}
