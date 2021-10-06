#include "Features/prompt.h"
#include "input.h"
#include "Helper/pipe.h"
#include "headers.h"
#include "Helper/linkedList.h"
#include "Features/processTermination.h"
#include <signal.h>
#include <stdlib.h>
#include "Features/history.h"

Fg fgDetails;

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

int main()
{
    clearFg();

    makeProcessLinkedList();
    setPromptVar();
    reset();

	signal(SIGINT, ctrlc);
	signal(SIGTSTP, ctrlz);
    signal(SIGCHLD, handleProcessTermination);

    while (1)
    {
        prompt();
        char* inp = input();

        addCommand(inp);

        for (char *safePtr, *token = strtok_r(inp, ";", &safePtr); token; token = strtok_r(NULL, ";", &safePtr))
            pipeIt(token);

        free(inp);
    }
    return 0;
}
