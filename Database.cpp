#include "Database.h"

Database::Database() {

}

Database::Database(string n, Relation R) {
	this->insert(pair<string, Relation>(n, R));
}

Relation Database::GetRelation(string n) {
	return this->at(n);
}

void Database::AddRelation(string n, Relation R) {
	this->insert(pair<string, Relation>(n, R));
}

void Database::ResetRelation(string n, Relation R) {
	this->at(n) = R;
}
