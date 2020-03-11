#include "Database.h"

Database::Database() {

}

Database::Database(string n, Relation R) {
	database.insert(pair<string, Relation> (n, R));
}

Relation Database::GetRelation(string n) {
	return database[n];
}

void Database::AddRelation(string n, Relation R) {
	database.insert(pair<string, Relation>(n, R));
}

void Database::SetRelation(string n, Tuple T) {
	database[n].AddTuple(T);
}

void Database::PrintDatabase() {
	cout << "In Print Database" << endl;
	cout << database.size() << endl;
	
	/*for (auto it : database) {
		for (size_t i = 0; i < 1; i++) {
			cout << this->size();
		}
	}*/
}
