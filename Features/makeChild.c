#include "../Helper/linkedList.h"
#include "../headers.h"
#include "makeChild.h"
#include <stdlib.h>

void makeChildFg(char** argv)
{
    pid_t pid = fork();

    switch(pid)
    {
    case 0:
        if (execvp(argv[0], argv) == -1)
            logError("Command not found");
        exit(0);

    case -1:
        logError("Error forking");
        return;

    default:
        addFgAr(pid, argv);
        int status;
        pid_t wpid = waitpid(pid, &status, WUNTRACED);
        clearFg();
    }
}

void makeChildBg(char** argv)
{
    pid_t pid = fork();

    switch(pid)
    {
    case 0:
        if (execvp(argv[0], argv) == -1)
        {
            char temp[100];
            logError("Command not found");
        }

        exit(0);

    case -1:
        logError("Error forking");
        return;

    default:
        addProcess(argv[0], argv, pid);
        printf("%u\n", pid);
    }
}
