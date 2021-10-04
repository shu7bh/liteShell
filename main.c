#include "prompt.h"
#include "input.h"
#include "runCommand.h"
#include "headers.h"
#include "linkedList.h"
#include "colors.h"
#include "processTermination.h"
#include <signal.h>
#include <stdlib.h>
#include "history.h"

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
            runCommand(token);
    }
    return 0;
}
