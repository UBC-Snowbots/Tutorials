#pragma once

struct Node {
	Node* parent;
	Node* left_child;
	Node* right_child;
	int value;
};

Node* NodeConstructor(Node* p, Node* lc, Node* rc, int val) {
	Node* this_node = 0;
	(*this_node).parent = p;
	(*this_node).left_child = lc;
	(*this_node).right_child = rc;
	(*this_node).value = val;
	return this_node;
}

void BFS(Node* starting_node, int goal_val);

bool CheckForGoal(Node* node, int goal);

// create graph here