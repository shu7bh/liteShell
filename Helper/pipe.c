#include "pipe.h"
#include "../headers.h"
#include "../runCommand.h"

void pipeIt(char* command)
{
    char* str = strdup(command);
    char* safePtr;

    int stdoutCopy = dup(STDOUT_FILENO);
    int stdinCopy = dup(STDIN_FILENO);
    int storeFd = stdinCopy;

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

        if (dup2(storeFd, STDIN_FILENO) < 0 || dup2(fd[1], STDOUT_FILENO) < 0)
        {
            perror("dup2 error");
            return;
        }

        if (storeFd != STDIN_FILENO)
            close(storeFd);

        if (fd[1] != STDOUT_FILENO)
            close(fd[1]);

        storeFd = fd[0];
        runCommand(argv[j]);
    }

    if (dup2(storeFd, STDIN_FILENO) < 0 || dup2(stdoutCopy, STDOUT_FILENO) < 0)
    {
        perror("dup2 error");
        return;
    }

    if (storeFd != STDIN_FILENO)
        close(storeFd);

    if (stdoutCopy != STDOUT_FILENO)
        close(stdoutCopy);

    runCommand(argv[i - 1]);
    free(str);

    /*dup2(stdinCopy, STDIN_FILENO);*/
    /*close(stdinCopy);*/
}
