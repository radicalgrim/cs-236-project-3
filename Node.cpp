#include "Node.h"

Node::Node() {
	ID = -1;
	isVisited = false;
	isSelfDependent = false;
}

Node::Node(int id) {
	ID = id;
	isVisited = false;
	isSelfDependent = false;
}

int Node::GetID() {
	return ID;
}

void Node::SetID(int id) {
	ID = id;
}

set<int> Node::GetAdjacentNodes() {
	return adjacentNodes;
}

void Node::SetAdjacentNode(int id) {
	adjacentNodes.insert(id);
}

bool Node::GetIsVisited() {
	return isVisited;
}

void Node::SetToVisited() {
	isVisited = true;
}

bool Node::GetIsSelfDep() {
	return isSelfDependent;
}

void Node::SetIsSelfDep(bool sd) {
	isSelfDependent = sd;
}
