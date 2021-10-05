#include "pipe.h"
#include "../headers.h"
#include "../runCommand.h"

void pipeIt(char* command)
{
    char* str = strdup(command);
    char* safePtr;

    int stdoutCopy = dup(STDOUT_FILENO);
    int stdinCopy = dup(STDIN_FILENO);

    char* argv[SIZE];

    int i = 0;
    for (char* token = strtok_r(command, "|", &safePtr); token; token = strtok_r(NULL, "|", &safePtr))
        argv[i++] = strdup(token);

    int fd[2];

    for (int j = 0; j < i - 1; ++j)
    {
        if (pipe(fd) == -1)
        {
            perror("Pipe error");
            return;
        }

        if (dup2(fd[1], STDOUT_FILENO) < 0)
        {
            perror("dup2 error");
            return;
        }

        if (fd[1] != STDOUT_FILENO)
            close(fd[1]);

        runCommand(argv[j]);

        if (dup2(fd[0], STDIN_FILENO) < 0)
        {
            perror("dup2 error");
            return;
        }

        if (fd[0] != STDIN_FILENO)
            close(fd[0]);
    }

    if (dup2(stdoutCopy, STDOUT_FILENO) < 0)
    {
        perror("dup2 error");
        return;
    }

    runCommand(argv[i - 1]);

    dup2(stdinCopy, STDIN_FILENO);
    free(str);

    close(stdinCopy);
    close(stdoutCopy);
}
