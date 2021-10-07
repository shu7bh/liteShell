#include "replay.h"
#include "../headers.h"
#include "../Helper/stringToNum.h"
#include "../runCommand.h"
#include "../Helper/callWriitenFunctions.h"
#include "../Features/makeChild.h"

void replay(char** argv, int argc)
{
    if (argc < 6)
    {
        logStdError("Inefficient number of arguments");
        return;
    }

    int flag[2] = {0};
    char str[2][SIZE] = {0};

    int start = 0, end = 0;

    char** command = malloc(sizeof(char*) * argc - 4);
    int ct = -1;

    for (int i = 1; i <= argc; ++i)
        if (!strcmp(argv[i], "-command"))
        {
            start = 1;
            end = 1;
        }
        else if (!strcmp(argv[i], "-interval"))
        {
            flag[0] = 1;
            end = 0;
            if (i + 1 > argc)
            {
                logStdError("Argument missing for interval");
                return;
            }
            strcpy(str[0], argv[++i]);
        }
        else if (!strcmp(argv[i], "-period"))
        {
            flag[1] = 1;
            end = 0;
            if (i + 1 > argc)
            {
                logStdError("Argument missing for period");
                return;
            }
            strcpy(str[1], argv[++i]);
        }
        else if (start && end)
            command[++ct] = strdup(argv[i]);

    if (!start && !flag[0] && !flag[1])
    {
        logStdError("All arguments not provided");
        return;
    }

    int val[2] = {0};
    val[0] = stringToNum(str[0]);
    val[1] = stringToNum(str[1]);

    if (val[0] == -1)
    {
        logStdError("interval needs an whole number agument");
        return;
    }

    if (val[1] == -1)
    {
        logStdError("period needs an whole number agument");
        return;
    }

    int bgFlag;
    if (!strcmp(command[ct], "&"))
        argv[ct--] = 0, bgFlag = 1;
    else
        bgFlag = 0;

    command[ct + 1] = 0;

    int num = val[1] / val[0];
    for (int i = 0; i < num; ++i)
    {
        sleep(val[0]);
        runCommand(command, ct, bgFlag);
    }

    for (int i = 0; i <= ct; ++i)
        free(command[i]);
    free(command);
    command = 0;
}
