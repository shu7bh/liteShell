#include "makeChild.h"
#include "headers.h"
#include "linkedList.h"
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
        wpid = waitpid(pid, &status, WUNTRACED);
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
