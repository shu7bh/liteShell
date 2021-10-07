#include "Features/processTermination.h"
#include "Features/signalHandler.h"
#include "Features/history.h"
#include "Features/prompt.h"
#include "Helper/linkedList.h"
#include "Helper/pipe.h"
#include "headers.h"
#include "input.h"
#include <signal.h>
#include <stdlib.h>

int main()
{
    clearFg();

    setPromptVar();
    loadHistory();
    makeProcessLinkedList();
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
