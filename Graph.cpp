#include "Graph.h"

Graph::Graph() {
}

map<int, Node> Graph::GetNodeMap() {
	return nodeMap;
}

void Graph::AddNode(int id, Node node) {
	nodeMap.insert(pair<int, Node>(id, node));
}

stack<int> Graph::GetTopSortedNodes() {
	return topSort;
}

void Graph::AddNodeTopSort(int index) {
	topSort.push(index);
}

vector<set<int>> Graph::GetSCC_List() {
	return SCC_List;
}

void Graph::AddSCC(set<int> scc) {
	SCC_List.push_back(scc);
}

void Graph::AddEdge(int from, int to) {

}

void Graph::DFS_Forest() {
	for (auto it : nodeMap) {
		if (!it.second.GetIsVisited()) {
			DFS(it.second);
		}
	}
}

void Graph::DFS(Node node) {
	if (node.GetIsVisited()) {
		return;
	}
	node.SetToVisited();
	for (auto it : node.GetAdjacentNodes()) {
		if (!nodeMap.at(it).GetIsVisited()) {
			DFS(nodeMap.at(it));
		}
	}
}
