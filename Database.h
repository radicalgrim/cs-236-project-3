#pragma once
#include "Relation.h"
#include <map>

class Database : public map<string, Relation> {
private:
	map<string, Relation> databaseMap;
public:
	Database();
	Database(string n, Relation R);
	Relation GetRelation(string n);
	void AddRelation(string n, Relation R);
	void SetRelation(string n, Tuple T);
	void PrintDatabase();
};

