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
        fg.pid = getpid();
        strcpy(fg.command, argv[0]);
        for (int i = 1; argv[i]; ++i)
        {
            strcat(fg.args, argv[i]);
            strcat(fg.args, " ");
        }
        wpid = waitpid(pid, &status, WUNTRACED);
        fg.pid = -1;
        memset(fg.command, 0, SIZE);
        memset(fg.args, 0, SIZE);
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
        addProcess(argv[0], pid);
        printf("%u\n", pid);
    }
}
