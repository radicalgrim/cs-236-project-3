#pragma once
#include "Relation.h"
#include <map>

class Database : public map<string, Relation> {
private:
public:
	Database();
	Database(string n, Relation R);
	Relation GetRelation(string n);
	void AddRelation(string n, Relation R);
	void ResetRelation(string n, Relation R);
};

