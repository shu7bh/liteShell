#include "makeChild.h"
#include "../headers.h"
#include "../Helper/linkedList.h"
#include <stdlib.h>

void makeChildFg(char** argv)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) // Child process
    {
        if (execvp(argv[0], argv))
            logError("Command not found");
        exit(0);
    }

    else if (pid < 0) // Error forking
        logError("Error forking");

    else // Parent process
    {
        fgDetails.pid = pid;
        strcpy(fgDetails.name, argv[0]);
        for (int i = 0; argv[i]; ++i)
        {
            strcat(fgDetails.command, argv[i]);
            strcat(fgDetails.command, " ");
        }
        wpid = waitpid(pid, &status, WUNTRACED);
        fgDetails.pid = -1;
        memset(fgDetails.name, 0, SIZE);
        memset(fgDetails.command, 0, SIZE);
    }
}

void makeChildBg(char** argv)
{
    pid_t pid, wpid;
    int status;

    pid = fork();

    if (pid == 0) // Child process
    {
        if (execvp(argv[0], argv) == -1)
        {
            char temp[100];
            logError("Command not found");
        }

        exit(0);
    }

    else if (pid < 0) // Error forking
        logError("Error forking");

    else // Parent process
    {
        addProcess(argv[0], argv, pid);
        printf("%u\n", pid);
    }
}
