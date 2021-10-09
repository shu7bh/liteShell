#include "../Helper/linkedList.h"
#include "../headers.h"
#include "makeChild.h"
#include "prompt.h"
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
        {
            int status;
            pid_t wpid = waitpid(pid, &status, WUNTRACED);

            if (WIFSTOPPED(status))
            {
                kill(pid, SIGTSTP);
                addProcess(argv[0], argv, pid);
                prompt();
            }
        }
    }
}

void makeChildBg(char** argv)
{
    pid_t pid = fork();

    switch(pid)
    {
    case 0:
        setpgid(0, 0);
        if (execvp(argv[0], argv) == -1)
        {
            logError("Command not found");
            prompt();
        }
        exit(0);

    case -1:
        logError("Error forking");
        return;

    default:
        setpgid(pid, 0);
        addProcess(argv[0], argv, pid);
    }
}
