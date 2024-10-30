#include <stdio.h>

int main(int argc, char** argv) 
{
    if (argc == 1) {
        puts("provide a file to parse");
        return 1;
    }

    FILE *fptr;
    if ((fptr = fopen(argv[1], "r")) == NULL) {
        printf("could not open file %s\n", argv[1]);
        return 1;
    }

    fclose(fptr);

    return 0;
}