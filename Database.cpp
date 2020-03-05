#include "Database.h"

Database::Database() {

}

Relation Database::GetRelation(string name) {
	return database[name];
}

void Database::PrintDatabase() {
	cout << "In Print Database" << endl;
	for (auto it : database) {
		for (size_t i = 0; i < 1; i++) {
			cout << this->size();
		}
	}
}
