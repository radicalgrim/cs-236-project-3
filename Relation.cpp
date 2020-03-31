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

bool Relation::AddTuple(Tuple t) {
	return tupleSet.insert(t).second;
}

void Relation::PrintRelation() {
	for (auto it : tupleSet) {
		for (size_t i = 0; i < scheme.GetLength(); i++) {
			if (i == 0) {
				cout << "  ";
			}
			cout << scheme.GetAttribute(i) << "=" << it.GetValue(i);
			if (i == scheme.GetLength() - 1) {
				cout << endl;
			}
			else {
				cout << ", ";
			}
		}
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


//void Relation::SelectSpecificValue(int index, string value) {
//	Relation newRelation = Relation(this->GetName(), this->GetScheme());
//	for (auto it : this->GetTupleSet()) {
//		if (it.GetValue(index) == value) {
//			newRelation.AddTuple(it);
//		}
//	}
//	*this = newRelation;
//}
