#include "runCommand.h"
#include "headers.h"
#include "Features/makeChild.h"
#include "Helper/token.h"
#include "Helper/callWriitenFunctions.h"
#include "Helper/inputOutputRedirection.h"
#include <string.h>
#include <fcntl.h>

void runCommand(char* inputBuffer)
{
    char* temp = strdup(inputBuffer);
    char** argv = malloc(SIZE);

    int* argc = malloc(sizeof(int));
    int* bgprocess = malloc(sizeof(int));
    if (!tokenize(inputBuffer, argv, argc, bgprocess))
        return;

    int stdoutCopy = dup(STDOUT_FILENO);
    int stdinCopy = dup(STDIN_FILENO);
    int stderrCopy = dup(STDERR_FILENO);

    if (!inputOutputRedirection(argv, argc))
    {
        dup2(stdoutCopy, STDOUT_FILENO);
        dup2(stdinCopy, STDIN_FILENO);
        dup2(stderrCopy, STDERR_FILENO);
        return;
    }

    if (!callWrittenFunctions(argv, *argc))
    {
        if (*bgprocess)
            makeChildBg(argv);
        else
            makeChildFg(argv);
    }

    strcpy(inputBuffer, temp);

    free(temp);
    free(argc);
    free(argv);
    free(bgprocess);

    dup2(stdoutCopy, STDOUT_FILENO);
    dup2(stdinCopy, STDIN_FILENO);
    dup2(stderrCopy, STDERR_FILENO);
}
