#pragma once
#include "node.h"

typedef struct {
    Node* root;
} DOM;

DOM* dom_init(void);
void dom_parse(DOM* dom, char* file_name);
void dom_destroy(DOM* dom);

void dom_print(DOM* dom);