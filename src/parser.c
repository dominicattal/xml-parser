#include "dom.h"
#include <stdio.h>

#define STACK_LIMIT 1000

static Node* stack[STACK_LIMIT];
static int stack_top;

static void parser_push(Node* node) 
{
    if (stack_top == STACK_LIMIT) {
        puts("Could not push");
        return;
    }
    stack[stack_top++] = node;
}

static Node* parser_pop(void) 
{
    if (stack_top == 0) {
        puts("Could not pop");
        return NULL;
    }
    return stack[--stack_top];
}

static void parser_helper(FILE* fptr) 
{
    char c;
    while ((c = fgetc(fptr)) != EOF)
        printf("%c", c);
}

void dom_parse(DOM* dom, char *file_name) 
{
    FILE* fptr = fopen(file_name, "r");
    if (fptr == NULL) {
        printf("could not open file %s\n", file_name);
        return;
    }

    stack_top = 0;
    parser_helper(fptr);

    fclose(fptr);
    return;
}


