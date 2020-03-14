#pragma once
#include "Tuple.h"
#include "Scheme.h"
#include <set>
#include <algorithm>

class Relation {
private:
	string name;
	Scheme scheme;
	set<Tuple> tupleSet;
public:
	Relation();
	Relation(string n);
	Relation(string n, Scheme s);
	Relation(string n, set<Tuple> T);
	void AddTuple(Tuple t);
	void PrintRelation();
	void SetName(string n);
	void SetScheme(Scheme S);
	string GetName();
	Scheme GetScheme();
	set<Tuple> GetTupleSet();
};

