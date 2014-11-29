#include "node.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

// create a new node
struct node * CreateEmptyNode()
{
	return 0;
}

// attach parent and children
void ConnectNodes(struct node * parent, struct node * lchild, struct node * rchild)
{
	parent->left_child = lchild;
	parent->right_child = rchild;
	lchild->parent = parent;
	rchild->parent = parent;
	return;
}

// Create a node with these properties
struct node * CreateNode(int value)
{
	struct node * new_node = new struct node;
	new_node->value = value;
	new_node->parent = 0;
	new_node->left_child = 0;
	new_node->right_child = 0;
	return new_node;	
}

// Using recursion to create a graph
struct node * RandomGraph(int num_of_nodes)
{
	if (num_of_nodes == 0) { return 0; }
	
	int random_value, number_of_children;
	random_value = rand() % 101; // random number between 0 and 100
	
	struct node * head = CreateNode(random_value);
	if (num_of_nodes == 1) { return head; }
	else if (num_of_nodes == 2) { 
		number_of_children = rand() % 2;
	}
	else {
		number_of_children = rand() % 3; // random number between 0 and 2
	}
	
	// only left child
	if (number_of_children == 0) {
		ConnectNodes(head, RandomGraph(num_of_nodes-1), 
	
	
	
}

// randomly generate graph
void GenerateGraph(struct node * start_node)
{
	int number_of_nodes = rand() % 20;
	
	
	
}

// Manually written graph for testing
struct node * MakeGraph() {

	struct node * cnode = new struct node;
	cnode->parent = 0;
	cnode->right_child = 0;
	cnode->value = 8;

	struct node * bnode = new struct node;
	bnode->parent = cnode;
	bnode->left_child = 0;
	bnode->right_child = 0;
	bnode->value = 6;

	cnode->left_child = bnode;
	delete bnode;
	
	return cnode;
}
