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

int main()
{
    makeProcessLinkedList();
    setPromptVar();
    reset();

    signal(SIGCHLD, handleProcessTermination);

    while (1)
    {
        prompt();
        char* inp = input();
        char* token, *safePtr;

        addCommand(inp);
        for (token = strtok_r(inp, ";", &safePtr); token; token = strtok_r(NULL, ";", &safePtr))
            pipeIt(token);
    }
    return 0;
}
