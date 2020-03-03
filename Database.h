#pragma once
#include "Relation.h"
#include <map>

class Database : public map<string, Relation> {
private:
	map<string, Relation> database;
public:
	Database();
	Relation GetRelation(string name);
};

