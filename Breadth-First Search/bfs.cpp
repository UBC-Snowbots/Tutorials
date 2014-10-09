#include "bfs.h"
#include <queue>
#include <iostream>

using namespace std;

queue<Node*> frontier;	// queue of nodes to check to find goal


int main() {
	return 0;
}


void BFS(Node* starting_node, int goal_val) {
	
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
			return; 
		}
		else { 
			frontier.push(currentNode->left_child);
			frontier.push(currentNode->right_child);
			frontier.pop(); 
		}
	}
	
	cout << "No goal found" << endl;
	
	}
}

bool CheckForGoal(Node* node, int goal);