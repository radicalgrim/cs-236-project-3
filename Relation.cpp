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
	Tuple myTup = Tuple();

	myTup.push_back("'33333'");
	myTup.push_back("'Snoopy'");

	for (unsigned i = 0; i < myTup.size(); i++) {
		cout << myTup[i];
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
