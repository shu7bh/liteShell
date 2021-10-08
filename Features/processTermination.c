#include "../Helper/linkedList.h"
#include "processTermination.h"
#include <sys/wait.h>
#include <unistd.h>
#include "prompt.h"
#include <stdio.h>

void handleProcessTermination(int sig)
{
    int flag;
    pid_t pid = waitpid(-1, &flag, WNOHANG);
    if(pid > 0)
    {
        char name[100];
        searchAndDeleteProcess(name, pid);

        if(WIFEXITED(flag))
            fprintf(stderr, "%s with pid = %d exited normally\n", name, pid);
        else
            fprintf(stderr, "%s with pid = %d exited abnormally\n", name, pid);

        prompt();
        fflush(stdout);
    }
}
