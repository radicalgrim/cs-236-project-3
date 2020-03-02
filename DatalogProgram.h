#pragma once
#include "Predicate.h"
#include "Rule.h"
#include <vector>
#include <set>

class DatalogProgram {
private:
	vector<Predicate> schemeList;
	vector<Predicate> factList;
	vector<Rule> ruleList;
	vector<Predicate> queryList;
	set<string> domain;
public:
	DatalogProgram();
	string toString();
	void SetSchemeList(vector<Predicate> parsedList);
	vector<Predicate> GetSchemeList();
	void SetFactList(vector<Predicate> parsedList);
	vector<Predicate> GetFactList();
	void SetRuleList(vector<Rule> parsedList);
	vector<Rule> GetRuleList();
	void SetQueryList(vector<Predicate> parsedList);
	vector<Predicate> GetQueryList();
	void SetDomain(string str);
	set<string> GetDomain();
};

