#include "node.h"
#include <stdlib.h>

// create a new node
void CreateEmptyNode(struct node * new_node)
{
	new_node->parent = 0;
	new_node->left_child = 0;
	new_node->right_child = 0;
	new_node->value = -1;
	return;
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


struct node* MakeGraph() {
struct node cnode;
cnode.parent = 0;
cnode.right_child = 0;
cnode.value = 8;

struct node bnode;
bnode.parent = &cnode;
bnode.left_child = 0;
bnode.right_child = 0;
bnode.value = 6;

cnode.left_child = &bnode;

return &cnode;
}