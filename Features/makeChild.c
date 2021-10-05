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
            perror("Command not found");
        exit(0);
    }

    else if (pid < 0) // Error forking
        perror("Error forking");

    else // Parent process
    {
        fgDetails.pid = getpid();
        strcpy(fgDetails.command, argv[0]);
        for (int i = 0; argv[i]; ++i)
        {
            strcat(fgDetails.args, argv[i]);
            strcat(fgDetails.args, " ");
        }
        wpid = waitpid(pid, &status, WUNTRACED);
        fgDetails.pid = -1;
        memset(fgDetails.command, 0, SIZE);
        memset(fgDetails.args, 0, SIZE);
    }
}

void makeChildBg(char** argv)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) // Child process
    {
        setpgid(0, 0);
        if (execvp(argv[0], argv) == -1)
        {
            char temp[100];
            perror("Command not found");
        }

        exit(0);
    }

    else if (pid < 0) // Error forking
        perror("Error forking");

    else // Parent process
    {
        addProcess(argv[0], argv, pid);
        printf("%u\n", pid);
    }
}
