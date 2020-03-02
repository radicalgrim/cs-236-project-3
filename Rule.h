#pragma once
#include "Predicate.h"


class Rule {
private:
	Predicate head;
	vector<Predicate> bodyList;
public:
	Rule();
	Rule(Predicate p);
	string toString();
	void SetHeadPredicate(Predicate h);
	Predicate GetHeadPredicate();
	void SetBodyPredicates(vector<Predicate> list);
	vector<Predicate> GetBodyPredicates();
};

