#include "node.h"
#include <stdlib.h>

Node* node_create(node_t type)
{
    Node* node = malloc(sizeof(Node));
    node->type = type;
    return node;
}

void node_add_child(Node* parent, Node* child)
{
    parent->children[parent->num_children++] = child;
}

void node_destroy(Node* node)
{
    free(node);
}