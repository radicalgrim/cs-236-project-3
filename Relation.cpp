#include "Relation.h"

Relation::Relation() {
}

Relation::Relation(string n) {
	name = n;
}

Relation::Relation(string n, Scheme s) {
	name = n;
	scheme = s;
}

Relation::Relation(string n, set<Tuple> T) {
	name = n;
	tupleSet = T;
}

void Relation::AddTuple(Tuple t) {
	tupleSet.insert(t);
}

void Relation::PrintRelation() {
	int count = 1;
	for (auto it : tupleSet) {
		cout << count << " " << tupleSet.size() << endl;
		for (size_t i = 0; i < scheme.GetLength(); i++) {
			cout << scheme.GetAttribute(i) << "=" << it.GetValue(i);
			if (i == scheme.GetLength() - 1) {
				cout << endl;
			}
			else {
				cout << ", ";
			}
		}
		count++;
	}
}

void Relation::SetName(string n) {
	name = n;
}

void Relation::SetScheme(Scheme S) {
	scheme = S;
}

string Relation::GetName() {
	return name;
}

Scheme Relation::GetScheme() {
	return scheme;
}

set<Tuple> Relation::GetTupleSet() {
	return tupleSet;
}
