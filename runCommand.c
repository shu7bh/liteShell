#include "Helper/inputOutputRedirection.h"
#include "Helper/callWriitenFunctions.h"
#include "Features/makeChild.h"
#include "Helper/changeIO.h"
#include "Helper/token.h"
#include "runCommand.h"
#include "headers.h"
#include <string.h>
#include <fcntl.h>

void preRunCommand(char* inputBuffer)
{
    char* temp = strdup(inputBuffer);

    if (!temp)
    {
        logError("strdup error");
        return;
    }

    char** argv = malloc(SIZE * sizeof(char*));

    if (!argv)
    {
        logError("malloc error");
        return;
    }

    int argc = 0;
    int bgFlag;

    if (!tokenize(inputBuffer, argv, &argc, &bgFlag))
        return;

    runCommand(argv, argc, bgFlag);

    for (int i = 0; i <= argc; ++i)
        if (argv[i])
            free(argv[i]);
    free(argv);
    free(temp);
    temp = 0;
    argv = 0;
}

void runCommand(char** argv, int argc, int bgFlag)
{
    int stdoutCopy = dup(STDOUT_FILENO);
    int stdinCopy = dup(STDIN_FILENO);

    if (!inputOutputRedirection(argv, &argc))
    {
        changeIO(stdoutCopy, STDOUT_FILENO);
        changeIO(stdinCopy, STDIN_FILENO);
        return;
    }

    if (!callWrittenFunctions(argv, argc, bgFlag))
        if (bgFlag)
            makeChildBg(argv);
        else
            makeChildFg(argv);
    else;

    changeIO(stdoutCopy, STDOUT_FILENO);
    changeIO(stdinCopy, STDIN_FILENO);
}
