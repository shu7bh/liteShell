#include "prompt.h"
#include "input.h"
#include "runCommand.h"
#include "headers.h"
#include "linkedList.h"
#include <signal.h>
#include "processTermination.h"

int main()
{
    makeProcessLinkedList();
    setPromptVar();
    setInputVar();

    signal(SIGCHLD, handleProcessTermination);

    while (1)
    {
        prompt();
        char* inputBuf = input();

        char* token;
        char* safePtr;
        for (token = strtok_r(inputBuf, ";", &safePtr); token; token = strtok_r(NULL, ";", &safePtr))
            runCommand(token);
    }
}
