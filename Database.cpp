#include "Database.h"

Database::Database() {

}

Database::Database(string n, Relation R) {
	databaseMap.insert(pair<string, Relation> (n, R));
}

Relation Database::GetRelation(string n) {
	return databaseMap[n];
}

void Database::AddRelation(string n, Relation R) {
	databaseMap.insert(pair<string, Relation>(n, R));
}

void Database::SetRelation(string n, Relation R) {
	databaseMap.at(n) = R;
}

void Database::PrintQueries(vector<string> queryList) {
	
	//for (size_t i = 0; i < queryList.size(); i++) {
	//	databaseMap.at(queryList[i]).PrintRelation();
	//}
	
	for (auto it : databaseMap) {
		for (size_t i = 0; i < 1; i++) {
			it.second.PrintRelation();
		}
	}
}
