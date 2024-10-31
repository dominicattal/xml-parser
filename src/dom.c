#include "dom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

DOM* dom_init(void) 
{
    DOM* dom = malloc(sizeof(DOM));
    dom->root = NULL;
    return dom;
}

void dom_destroy(DOM* dom)
{
    free(dom->root);
    free(dom);
}

static void indent(int depth)
{
    for (int i = 0; i < depth; i++)
        printf("   ");
}

static void print_helper(Node* node, int depth)
{
    indent(depth);
    puts(node->data);
    for (int i = 0; i < node->num_children; i++)
        print_helper(node->children[i], depth + 1);
    if (node->type != TEXT_NODE) {
        indent(depth);
        printf("/%s\n", node->data);
    }
}

void dom_print(DOM* dom)
{
    print_helper(dom->root, 0);
}