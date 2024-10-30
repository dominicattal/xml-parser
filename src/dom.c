#include "dom.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

DOM* dom_init(void) 
{
    DOM* dom = malloc(sizeof(DOM));
    dom->root = NULL;
    return dom;
}

typedef struct {
    int closing_tag;
    union {
        char data[MAX_LENGTH+1];
        Node* node;
    };
} parser_t;

static parser_t parser_helper(FILE* fptr) 
{
    char c;
    parser_t ret;
    ret.closing_tag = 0;
    int i = 0;

    while (isspace(c = fgetc(fptr)))
        ;

    if (c != '<') {
        // text
        ret.node = node_create(TEXT_NODE);
        ret.node->data[i++] = c;
        for (c = fgetc(fptr); c != EOF && c != '<'; c = fgetc(fptr))
            if (i < MAX_LENGTH)
                ret.node->data[i++] = c;
        ret.node->data[i] = '\0';
        ungetc(c, fptr);
        printf("Text node: %s\n", ret.node->data);
        return ret;
    }
    c = fgetc(fptr);
    if (c != '/') {
        // opening tag
        ret.node = node_create(ELMT_NODE);
        ret.node->data[i++] = c;
        for (c = fgetc(fptr); c != EOF && c != '>'; c = fgetc(fptr))
            if (i < MAX_LENGTH)
                ret.node->data[i++] = c;
        ret.node->data[i] = '\0';
        printf("Element node: %s\n", ret.node->data);
        parser_t next = parser_helper(fptr);
        while (!next.closing_tag) {
            node_add_child(ret.node, next.node);
            next = parser_helper(fptr);
        }
        return ret;
    } else {
        // closing tag
        ret.closing_tag = 1;
        for (c = fgetc(fptr); c != EOF && c != '>'; c = fgetc(fptr))
            if (i < MAX_LENGTH)
                ret.data[i++] = c;
        ret.data[i] = '\0';
        printf("Closing tag: %s\n", ret.data);
        return ret;
    }
    return ret;
}

void dom_parse(DOM* dom, char *file_name) 
{
    FILE* fptr = fopen(file_name, "r");
    if (fptr == NULL) {
        printf("could not open file %s\n", file_name);
        return;
    }

    parser_t res = parser_helper(fptr);

    fclose(fptr);
    return;
}


void dom_destroy(DOM* dom)
{
    free(dom->root);
    free(dom);
}
