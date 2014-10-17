#include "node.h"
#include <queue>
#include <iostream>

using namespace std;


// VARIABLES

queue<struct node *> frontier;	// queue of nodes to check to find goal


// initiates function names, output type, and inputs

void BFS(struct node * starting_node, int goal_val);

bool CheckForGoal(struct node* node, int goal);


// MAIN FUNCTION

int main() {
	BFS(CreateEmptyNode(), 7);
	BFS(MakeGraph(), 6);
	return 0;
}


// FUNCTIONS

// checks whether node contains goal value
bool CheckForGoal(struct node* node, int goal) {
	if (node->value == goal) { return true; }
	else { return false; }
}

// this is the breadth-first search algorithm
void BFS(struct node * starting_node, int goal_val) {

	// check for null graph
	if (starting_node == 0) {
		cout << "Graph does not exist" << endl;
		return;
	}

	// otherwise put it into the frontier
	frontier.push(starting_node);
	
	struct node* currentNode = 0;
	
	// search through graph using bfs until goal is found or end of graph
	while (!frontier.empty()) {
	
		currentNode = frontier.front();
		
		if (CheckForGoal(currentNode, goal_val)) { 
			cout << "Goal: " << (*currentNode).value << endl;
			return; 
		}
		
		else { 
			if (currentNode->left_child) { frontier.push(currentNode->left_child); }
			if (currentNode->right_child) { frontier.push(currentNode->right_child); }
			frontier.pop(); 
		}
	}
	
	cout << "No goal found" << endl;
	return;
}