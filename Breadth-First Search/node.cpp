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

// randomly generate graph
void GenerateGraph(struct node * start_node)
{
	int number_of_nodes = rand() % 30;
	
}


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
