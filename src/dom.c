#include "dom.h"
#include <stdio.h>
#include <stdlib.h>

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
