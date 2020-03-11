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
	string GetAttribute(int index);
	void AddAttribute(string a);
	int GetLength();
};