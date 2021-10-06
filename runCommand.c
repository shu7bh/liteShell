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
    int argc = 0;
    int bgprocess;

    if (!tokenize(inputBuffer, argv, &argc, &bgprocess))
        return;

    int stdoutCopy = dup(STDOUT_FILENO);
    int stdinCopy = dup(STDIN_FILENO);

    if (!inputOutputRedirection(argv, &argc))
    {
        dup2(stdoutCopy, STDOUT_FILENO);
        dup2(stdinCopy, STDIN_FILENO);
        return;
    }

    if (!callWrittenFunctions(argv, argc))
    {
        if (bgprocess)
            makeChildBg(argv);
        else
            makeChildFg(argv);
    }

    strcpy(inputBuffer, temp);


    for (int i = 0; i <= argc; ++i)
        free(argv[i]);

    free(temp);
    free(argv);

    if (dup2(stdoutCopy, STDOUT_FILENO) < 0 || dup2(stdinCopy, STDIN_FILENO) < 0)
    {
        logError("Dup2 error");
        return;
    }

    /*if (stdinCopy != STDIN_FILENO)*/
        /*close(stdinCopy);*/

    if (stdoutCopy != STDOUT_FILENO)
        close(stdoutCopy);
}
