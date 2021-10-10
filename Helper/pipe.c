#include "../Helper/changeIO.h"
#include "../runCommand.h"
#include "../headers.h"
#include "pipe.h"

void pipeIt(char* command)
{
    char* str = strdup(command);
    if (!str)
    {
        logError("strdup error");
        return;
    }

    char* safePtr;

    int stdoutCopy = dup(STDOUT_FILENO);
    int stdinCopy = dup(STDIN_FILENO);

    char* argv[SIZE];

    int i = 0;
    for (char* token = strtok_r(str, "|", &safePtr); token; token = strtok_r(NULL, "|", &safePtr))
    {
        argv[i++] = strdup(token);

        if (!argv[i - 1])
        {
            logError("strdup error");
            for (int j = 0; j < i; ++j)
                free (argv[j]);
            free(str);
            return;
        }
    }

    int fd[2];
    color = 0;

    for (int j = 0; j < i - 1; ++j)
    {
        if (pipe(fd) == -1)
        {
            logError("Pipe error");
            return;
        }
        changeIO(fd[1], STDOUT_FILENO);
        preRunCommand(argv[j]);
        changeIO(fd[0], STDIN_FILENO);
    }

    changeIO(stdoutCopy, STDOUT_FILENO);
    color = 1;
    preRunCommand(argv[i - 1]);
    changeIO(stdinCopy, STDIN_FILENO);

    for (int j = 0; j <= i; ++j)
        if (argv[i])
        {
            free(argv[i]);
            argv[i] = 0;
        }
    free(str);
}
