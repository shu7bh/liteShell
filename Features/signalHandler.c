#include "signalHandler.h"
#include "../headers.h"
#include "../Helper/linkedList.h"

void ctrlc(int sig)
{
    if (fgDetails.pid != -1)
    {
        kill(fgDetails.pid, SIGINT);
        clearFg();
        printf("\r");
    }
}

void ctrlz(int sig)
{
    printf("\r");
    if (fgDetails.pid != -1)
    {
        kill(fgDetails.pid, SIGTSTP);
        char* command[2];
        command[0] = strdup(fgDetails.command);
        command[1] = 0;

        addProcess(fgDetails.name, command, fgDetails.pid);
        free(command[0]);

        clearFg();
    }
}
