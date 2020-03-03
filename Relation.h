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
	Relation(string n, Scheme s);
	void AddTuple(Tuple t);
	void PrintRelations();
	void ToString(int i);
	/*
	select(int index, string value);
	select(int index1, int index2);
	project(vector<int> indexes);
	rename(vector<string> names);
	R1 = R2.select();
	*/
};

