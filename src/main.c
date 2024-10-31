#include <stdio.h>
#include "dom.h"

int main(int argc, char** argv) 
{
    if (argc == 1) {
        puts("Provide a file to parse");
        return 1;
    }

    DOM* dom = dom_init();
    dom_parse(dom, argv[1]);
    dom_print(dom);

    return 0;
}