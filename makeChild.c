#include "makeChild.h"
#include "headers.h"
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
        setpgid(pid, pid);
        if (execvp(argv[0], argv))
            perror("Command not found");
        exit(0);
    }

    else if (pid < 0) // Error forking
        perror("Error forking");

    else // Parent process
    {
        setpgid(pid, pid);
        printf("%u\n", pid);
    }
}
