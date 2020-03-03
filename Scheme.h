#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Scheme {
private:
	vector<string> nameList;
public:
	Scheme();
	string GetAttribute(int index);
	int GetLength();
};