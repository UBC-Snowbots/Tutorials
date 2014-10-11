#include "node.cpp"

#pragma once

// creates a node structure
struct node {
	struct node * parent;
	struct node * left_child;
	struct node * right_child;
	int value;
};


// create a new node
void CreateEmptyNode(struct node * new_node);

// attach parent and children
void ConnectNodes(struct node * parent, struct node * lchild, struct node * rchild);

// randomly generate graph
void GenerateGraph(struct node * start_node);

// placeholder
struct node* MakeGraph();