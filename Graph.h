#pragma once
#include "Node.h"
#include <map>
#include <stack>
#include <vector>

class Graph {
private:
	map<int, Node> nodeMap;
	stack<int> topSort;
	vector<set<int>> SCC_List;
public:
	Graph();
	map<int, Node> GetNodeMap();
	void AddNode(int id, Node node);
	stack<int> GetTopSortedNodes();
	void AddNodeTopSort(int index);
	vector<set<int>> GetSCC_List();
	void AddSCC(set<int> scc);
	void AddEdge(int from, int to);
	void DFS_Forest();
	void DFS(Node node);
};

