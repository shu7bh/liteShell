#include "../Helper/callWriitenFunctions.h"
#include "../Helper/stringToNum.h"
#include "../headers.h"
#include "../runCommand.h"
#include "makeChild.h"
#include "repeat.h"
#include <stdlib.h>

void repeat(int argc, char** argv, int bgFlag)
{
    if (argc == 1)
    {
        logStdError("repeat error: No number provided");
        return;
    }

    int num = stringToNum(argv[1]);

    if (num < 0)
    {
        logStdError("Give a whole number");
        return;
    }

    char** command = malloc(sizeof(char*) * argc - 1);
    int ct = -1;

    for (int i = 2; i <= argc; ++i)
        command[++ct] = strdup(argv[i]);

    command[ct + 1] = 0;

    for (int i = 0; i < num; ++i)
        runCommand(command, ct, bgFlag);
}
