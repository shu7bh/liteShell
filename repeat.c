#include "repeat.h"
#include "headers.h"
#include "makeChild.h"
#include "stringToNum.h"
#include <stdlib.h>

void repeat(int argc, char** argv)
{
    if (argc == 1)
    {
        printf("repeat error: No number provided\n");
        return;
    }

    int num = stringToNum(argv[1]);

    for (int i = 0; i < num; ++i)
        makeChildFg(argv + 2);
}
