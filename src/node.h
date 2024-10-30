#pragma once

typedef enum {
    TEXT_NODE,
    ATTR_NODE,
    ELMT_NODE
} node_t;

typedef struct Node Node;

typedef struct Node {
    node_t type;
    int num_children;
    Node* children[10];
} Node;

Node* node_create(node_t type);
void node_add_child(Node* parent, Node* child);
void node_destroy(Node* node);
