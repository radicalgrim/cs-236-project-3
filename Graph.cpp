#include "Graph.h"

Graph::Graph() {
}

Node Graph::GetNode(int id) {
	return nodeMap.at(id);
}

map<int, Node> Graph::GetNodeMap() {
	return nodeMap;
}

void Graph::AddNode(int id, Node node) {
	nodeMap.insert(pair<int, Node>(id, node));
}

void Graph::SetNodeSelfDep(int id) {
	nodeMap.at(id).SetIsSelfDep();
}

stack<int> Graph::GetPostOrderNums() {
	return postOrderNums;
}

void Graph::PopPostOrderNum() {
	postOrderNums.pop();
}

void Graph::SetPostOrderNum(int index) {
	postOrderNums.push(index);
}

vector<set<int>> Graph::GetSCC_List() {
	return SCC_List;
}

void Graph::AddSCC(set<int> scc) {
	SCC_List.push_back(scc);
}

void Graph::AddEdge(int from, int to) {
	nodeMap.at(from).SetAdjacentNode(to);
}

void Graph::DFS_Forest() {
	set<int> component;
	for (auto it : nodeMap) {
		if (!it.second.GetIsVisited()) {
			DFS(it.first, component);
		}
	}
}

void Graph::DFS(int id, set<int>& component) {
	if (nodeMap.at(id).GetIsVisited()) {
		return;
	}
	component.insert(id);
	nodeMap.at(id).SetToVisited();
	for (auto it : nodeMap.at(id).GetAdjacentNodes()) {
		if (!nodeMap.at(it).GetIsVisited()) {
			DFS(it, component);
		}
	}
	SetPostOrderNum(id);
}
