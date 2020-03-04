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
		for (size_t i = 0; i < *it.size(); i++) {
			cout << scheme[i] << "=" << *it[i] << ", ";
		}
	}
}

void Relation::ToString(int i) {
	for (size_t j = 0; j < scheme.GetLength(); j++) {
		cout << scheme.GetAttribute(j) << "=";
	}
}
