#pragma once
#include <set>
using namespace std;

class Node {
private:
	int ID;
	set<int> adjacentNodes;
	bool isVisited;
	bool isSelfDependent;
public:
	Node();
	Node(int id);
	int GetID();
	void SetID(int id);
	set<int> GetAdjacentNodes();
	void SetAdjacentNode(int id);
	bool GetIsVisited();
	void SetToVisited();
	bool GetIsSelfDep();
	void SetIsSelfDep(bool sd);
};

