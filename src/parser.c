#include "dom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NODE_STATE 0
#define CLOSING_STATE 1
#define EOF_STATE 2

typedef struct {
    int state;
    union {
        char data[MAX_LENGTH+1];
        Node* node;
    };
} parser_t;

static char next_nonspace(FILE* fptr) {
    char c = fgetc(fptr);
    while (c != EOF && isspace(c))
        c = fgetc(fptr);
    return c;
}

static parser_t parser_helper(FILE* fptr) 
{
    char c;
    parser_t ret;
    ret.state = NODE_STATE;
    int i = 0;
    
    if ((c = next_nonspace(fptr)) == EOF) {
        ret.state = EOF_STATE;
        return ret;
    }

    if (c != '<') {
        // text
        ret.node = node_create(TEXT_NODE);
        ret.node->data[i++] = c;
        for (c = fgetc(fptr); c != EOF && c != '<'; c = fgetc(fptr))
            if (i < MAX_LENGTH)
                ret.node->data[i++] = c;
        ret.node->data[i] = '\0';
        ungetc(c, fptr);
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
        if (c == EOF) {
            ret.state = EOF_STATE;
            return ret;
        }
        parser_t next = parser_helper(fptr);
        while (next.state == NODE_STATE) {
            node_add_child(ret.node, next.node);
            next = parser_helper(fptr);
        }
        if (next.state == EOF_STATE) {
            printf("Missing closing tag for: %s\n", ret.node->data);
            exit(1);
        }
        if (strcmp(ret.node->data, next.data)) {
            printf("Mismatched closing tag for: %s\n", ret.node->data);
            exit(1);
        }
    } else {
        // closing tag
        ret.state = CLOSING_STATE;
        for (c = fgetc(fptr); c != EOF && c != '>'; c = fgetc(fptr))
            if (i < MAX_LENGTH)
                ret.data[i++] = c;
        ret.data[i] = '\0';
        if (c == EOF)
            ret.state = EOF_STATE;
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
    if (res.state == NODE_STATE)
        dom->root = res.node;

    fclose(fptr);
    return;
}