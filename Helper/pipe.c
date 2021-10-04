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

    int fd[2];

    for (char* token = strtok_r(command, "|", &safePtr); token; token = strtok_r(NULL, "|", &safePtr))
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

        printf("%d\n%d\n", STDIN_FILENO, STDOUT_FILENO);

        close(storeFd);
        close(fd[1]);

        storeFd = fd[0];
        runCommand(token);
    }

    char string[SIZE];

    dup2(stdinCopy, STDIN_FILENO);
    dup2(stdoutCopy, STDOUT_FILENO);

    while (read(storeFd, string, SIZE))
        printf("%s", string);
    free(str);
}
