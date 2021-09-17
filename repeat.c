#include "repeat.h"
#include "headers.h"
#include "makeChild.h"
#include <stdlib.h>

void repeat(int argc, char** argv)
{
    if (argc == 1)
    {
        printf("repeat error: No number provided\n");
        return;
    }

    int num = 0;
    for (int i = 0; i < strlen(argv[1]); ++i)
    {
        num *= 10;
        int ascii = argv[1][i] - '0';
        if (ascii > 9 || ascii < 0)
        {
            printf("repeat error: Number is not provided\n");
            return;
        }
        num += ascii;
    }

    for (int i = 0; i < num; ++i)
        makeChildFg(argv + 2);
}
