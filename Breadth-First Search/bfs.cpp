//#include "bfs.h"
#include <queue>
#include <iostream>

using namespace std;

struct node {
	struct node * parent;
	struct node * left_child;
	struct node * right_child;
	int value;
};


queue<struct node *> frontier;	// queue of nodes to check to find goal



bool CheckForGoal(struct node* node, int goal) {
	if (node->value == goal) { return true; }
	else { return false; }
}


void BFS(struct node * starting_node, int goal_val) {

	// check for null graph
	if (starting_node == 0) {
		cout << "Graph does not exist" << endl;
		return;
	}

	// otherwise put it into the frontier
	frontier.push(starting_node);
	
	struct node* currentNode = 0;
	
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



int main() {

struct node cnode;
cnode.parent = 0;
cnode.left_child = 0;
cnode.right_child = 0;
cnode.value = 7;

	BFS(&cnode, 7);
	return 0;
}
