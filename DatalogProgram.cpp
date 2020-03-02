#include "DatalogProgram.h"

DatalogProgram::DatalogProgram() {

}

string DatalogProgram::toString() {
	string str = "";

	str += "Schemes(" + to_string(schemeList.size()) + "):\n";
	for (size_t i = 0; i < schemeList.size(); i++) {
		str += "  " + schemeList[i].toString() + "\n";
	}

	str += "Facts(" + to_string(factList.size()) + "):\n";
	for (size_t i = 0; i < factList.size(); i++) {
		str += "  " + factList[i].toString() + ".\n";
	}

	str += "Rules(" + to_string(ruleList.size()) + "):\n";
	for (size_t i = 0; i < ruleList.size(); i++) {
		str += "  " + ruleList[i].toString() + ".\n";
	}

	str += "Queries(" + to_string(queryList.size()) + "):\n";
	for (size_t i = 0; i < queryList.size(); i++) {
		str += "  " + queryList[i].toString() + "?\n";
	}

	str += "Domain(" + to_string(domain.size()) + "):\n";
	set<string>::iterator it = domain.begin();
	for (it = domain.begin(); it != domain.end(); it++) {
		str += "  " + *it + "\n";
	}

	return str;
}

void DatalogProgram::SetSchemeList(vector<Predicate> parsedList) {
	for (size_t i = 0; i < parsedList.size(); i++) {
		schemeList.push_back(parsedList[i]);
	}
}

vector<Predicate> DatalogProgram::GetSchemeList() {
	return schemeList;
}

void DatalogProgram::SetFactList(vector<Predicate> parsedList) {
	for (size_t i = 0; i < parsedList.size(); i++) {
		factList.push_back(parsedList[i]);
	}
}

vector<Predicate> DatalogProgram::GetFactList() {
	return factList;
}

void DatalogProgram::SetRuleList(vector<Rule> parsedList) {
	for (size_t i = 0; i < parsedList.size(); i++) {
		ruleList.push_back(parsedList[i]);
	}
}

vector<Rule> DatalogProgram::GetRuleList() {
	return ruleList;
}

void DatalogProgram::SetQueryList(vector<Predicate> parsedList) {
	for (size_t i = 0; i < parsedList.size(); i++) {
		queryList.push_back(parsedList[i]);
	}
}

vector<Predicate> DatalogProgram::GetQueryList() {
	return queryList;
}

void DatalogProgram::SetDomain(string str) {
	domain.insert(str);
}

set<string> DatalogProgram::GetDomain() {
	return domain;
}
