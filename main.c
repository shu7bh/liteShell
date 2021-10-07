#include "Features/processTermination.h"
#include "Features/signalHandler.h"
#include "Features/history.h"
#include "Features/prompt.h"
#include "Helper/linkedList.h"
#include "Helper/homeDir.h"
#include "Helper/pipe.h"
#include "headers.h"
#include "input.h"
#include <signal.h>
#include <stdlib.h>

void displayGraphicArt();

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

    displayGraphicArt();

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

void displayGraphicArt()
{
    char path[SIZE] = {0};
    sprintf(path, "%s/.liteShell/asciiGrapic.txt", getHomeDir());

    FILE* fp = fopen(path, "r");
    if (!fp)
    {
        logError("fopen error");
        return;
    }

    char *str = malloc(SIZE);
    size_t size = SIZE;

    magenta();
    printf("\n\n");

    while (getline(&str, &size, fp) != -1)
        printf("%s", str);

    printf("\n");
    reset();

    free(str);
}
