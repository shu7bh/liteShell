#include "pipe.h"
#include "../headers.h"
#include "../runCommand.h"
#include "../Helper/changeIO.h"

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
        changeIO(fd[1], STDOUT_FILENO);
        runCommand(argv[j]);
        changeIO(fd[0], STDIN_FILENO);
    }

    changeIO(stdoutCopy, STDOUT_FILENO);
    runCommand(argv[i - 1]);
    changeIO(stdinCopy, STDIN_FILENO);

    free(str);

    close(stdinCopy);
    close(stdoutCopy);
}
