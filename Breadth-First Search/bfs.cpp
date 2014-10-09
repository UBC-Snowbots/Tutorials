//#include "bfs.h"
#include <queue>
#include <iostream>

using namespace std;

struct Node {
	Node* parent;
	Node* left_child;
	Node* right_child;
	int value;
};

queue<struct Node*> frontier;	// queue of nodes to check to find goal

struct Node cnode;
cnode.parent = 0;
cnode.left_child = 0;
cnode.right_child = 0;
cnode.value = 7;




void BFS(struct Node* starting_node, int goal_val) {
		cout << "here" << endl;
	// check for null graph
	if (starting_node == 0) {
		cout << "Graph does not exist" << endl;
		return;
	}

	// otherwise put it into the frontier
	frontier.push(starting_node);
	
	Node* currentNode = 0;
	
	// 
	while (!frontier.empty()) {
	
		currentNode = frontier.front();
		
		if (CheckForGoal(currentNode, goal_val)) { 
			cout << "Goal: " << (*currentNode).value << endl;
			return; 
		}
		
		else { 
			frontier.push(currentNode->left_child);
			frontier.push(currentNode->right_child);
			frontier.pop(); 
		}
	}
	
	cout << "No goal found" << endl;
	return;
}

bool CheckForGoal(Node* node, int goal) {
	if (node->value == goal) { return true; }
	else { return false; }
}

int main() {
	BFS(&cnode, 7);
	return 0;
}
