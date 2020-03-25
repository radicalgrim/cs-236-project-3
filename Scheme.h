#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Scheme {
private:
	vector<string> attributeList;
public:
	Scheme();
	vector<string> GetAttributeList();
	string GetAttribute(int index);
	void AddAttribute(string a);
	size_t GetLength();
};