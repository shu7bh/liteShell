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

Fg fg;

void ctrlc(int sig)
{
    if (fg.pid != -1)
    {
        kill(fg.pid, SIGINT);
        fg.pid = -1;
        memset(fg.command, 0, SIZE);
        memset(fg.args, 0, SIZE);

        printf("\r");
    }
    /*else*/
    /*{*/
        /*printf("\n");*/
        /*prompt();*/
    /*}*/
}

void ctrlz(int sig)
{
	signal(SIGTSTP, ctrlz);
    if (fg.pid != -1)
    {
        printf("%d", fg.pid);
        kill(fg.pid, SIGTSTP);
        addCommand(fg.command);
        fg.pid = -1;
        memset(fg.command, 0, SIZE);
        memset(fg.args, 0, SIZE);
    }
}

int main()
{
    fg.pid = -1;
    memset(fg.command, 0, SIZE);
    memset(fg.args, 0, SIZE);

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
