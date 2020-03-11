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

void Relation::AddTuple(Tuple t) {
	tupleSet.insert(t);
}

void Relation::PrintRelations() {

	for (size_t i = 0; i < tupleSet.size(); i++) {
		cout << this->GetName();
	}


	//for (auto it = tupleSet.begin(); it != tupleSet.end(); it++) {
	//	
	//	this->size();

	//	//for (size_t i = 0; i < *it.size(); i++) {
	//	//	cout << scheme[i] << "=" << *it[i] << ", ";
	//	//}
	//}
}

void Relation::ToString(int i) {
	for (size_t j = 0; j < scheme.GetLength(); j++) {
		cout << scheme.GetAttribute(j) << "=";
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
