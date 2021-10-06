#include "repeat.h"
#include "../headers.h"
#include "makeChild.h"
#include "../Helper/stringToNum.h"
#include "../Helper/callWriitenFunctions.h"
#include <stdlib.h>

void repeat(int argc, char** argv)
{
    if (argc == 1)
    {
        logStdError("repeat error: No number provided");
        return;
    }

    int num = stringToNum(argv[1]);

    for (int i = 0; i < num; ++i)
        if (!callWrittenFunctions(argv + 2, argc - 2))
            makeChildFg(argv + 2);
}
