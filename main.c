#include "Features/prompt.h"
#include "input.h"
#include "Helper/pipe.h"
#include "headers.h"
#include "Helper/linkedList.h"
#include "Helper/colors.h"
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
        fgDetails.pid = -1;
        memset(fgDetails.command, 0, SIZE);
        memset(fgDetails.args, 0, SIZE);

        printf("\r");
    }
}

void ctrlz(int sig)
{
    /*printf("%d %s %s\n", fgDetails.pid, fgDetails.command, fgDetails.args);*/
    if (fgDetails.pid != -1)
    {
        /*printf("%d", fgDetails.pid);*/
        kill(fgDetails.pid, SIGTSTP);
        char* args[2];
        args[0] = strdup(fgDetails.args);
        args[1] = 0;

        addProcess(fgDetails.command, args, fgDetails.pid);
        fgDetails.pid = -1;

        free(args[0]);
        memset(fgDetails.command, 0, SIZE);
        memset(fgDetails.args, 0, SIZE);
    }
}

int main()
{
    fgDetails.pid = -1;
    memset(fgDetails.command, 0, SIZE);
    memset(fgDetails.args, 0, SIZE);

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
        char* token, *safePtr;

        addCommand(inp);
        for (token = strtok_r(inp, ";", &safePtr); token; token = strtok_r(NULL, ";", &safePtr))
            pipeIt(token);

        free(inp);
    }
    return 0;
}
