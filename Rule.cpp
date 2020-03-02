#include "Rule.h"

Rule::Rule() {

}

Rule::Rule(Predicate p) {
	head = p;
}

string Rule::toString() {
	string str = "";

	str += head.toString() + " :- ";
	for (size_t i = 0; i < bodyList.size(); i++) {
		str += bodyList[i].toString();
		if (i != bodyList.size() - 1) {
			str += ",";
		}
	}

	return str;
}

void Rule::SetHeadPredicate(Predicate h) {
	head = h;
}

Predicate Rule::GetHeadPredicate() {
	return head;
}

void Rule::SetBodyPredicates(vector<Predicate> list) {
	for (size_t i = 0; i < list.size(); i++) {
		bodyList.push_back(list[i]);
	}
}

vector<Predicate> Rule::GetBodyPredicates() {
	return bodyList;
}
