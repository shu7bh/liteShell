#include "runCommand.h"
#include "headers.h"
#include "Features/makeChild.h"
#include "Helper/token.h"
#include "Helper/callWriitenFunctions.h"
#include "Helper/inputOutputRedirection.h"
#include "Helper/changeIO.h"
#include <string.h>
#include <fcntl.h>

void runCommand(char* inputBuffer)
{
    char* temp = strdup(inputBuffer);
    char** argv = malloc(SIZE);
    int argc = 0;
    int bgprocess;

    if (!tokenize(inputBuffer, argv, &argc, &bgprocess))
        return;

    int stdoutCopy = dup(STDOUT_FILENO);
    int stdinCopy = dup(STDIN_FILENO);

    if (!inputOutputRedirection(argv, &argc))
    {
        changeIO(stdoutCopy, STDOUT_FILENO);
        changeIO(stdinCopy, STDIN_FILENO);
        return;
    }

    if (!callWrittenFunctions(argv, argc))
        if (bgprocess)
            makeChildBg(argv);
        else
            makeChildFg(argv);
    else;

    for (int i = 0; i <= argc; ++i)
        free(argv[i]);
    free(argv);

    changeIO(stdoutCopy, STDOUT_FILENO);
    changeIO(stdinCopy, STDIN_FILENO);
}
