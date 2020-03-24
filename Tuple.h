#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Tuple : public vector<string> {
private:
public:	
	Tuple();
	string GetValue(int i);
	void AddValue(string v);
};

