#pragma once
#include "Node.h"
#include <map>
#include <stack>
#include <vector>

class Graph {
private:
	map<int, Node> nodeMap;
	stack<int> postOrderNums;
	vector<set<int>> SCC_List;
public:
	Graph();
	Node GetNode(int id);
	map<int, Node> GetNodeMap();
	void AddNode(int id, Node node);
	void SetNodeSelfDep(int id);
	stack<int> GetPostOrderNums();
	void PopPostOrderNum();
	void SetPostOrderNum(int index);
	vector<set<int>> GetSCC_List();
	void AddSCC(set<int> scc);
	void AddEdge(int from, int to);
	void DFS_Forest();
	void DFS(int id, set<int>& component);
};

