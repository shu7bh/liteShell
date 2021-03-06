#include "../Helper/callWriitenFunctions.h"
#include "../Features/makeChild.h"
#include "../Helper/stringToNum.h"
#include "../runCommand.h"
#include "../headers.h"
#include "replay.h"

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

    if (!command)
    {
        logError("malloc error");
        return;
    }

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

    if (val[0] <= 0)
    {
        logStdError("interval needs a number greater than 0");
        return;
    }

    if (val[1] <= 0)
    {
        logStdError("period needs a number greater than 0");
        return;
    }

    int bgFlag;
    if (!strcmp(command[ct], "&"))
        command[ct--] = 0, bgFlag = 1;
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
