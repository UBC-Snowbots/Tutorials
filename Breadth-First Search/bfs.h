#pragma once

struct Node {
	Node* parent;
	Node* left_child;
	Node* right_child;
	int value;
};

void BFS(Node* starting_node, int goal_val);

bool CheckForGoal(Node* node, int goal);

