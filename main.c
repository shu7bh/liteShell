#include "Features/processTermination.h"
#include "Features/signalHandler.h"
#include "Helper/linkedList.h"
#include "Features/history.h"
#include "Features/prompt.h"
#include "Helper/homeDir.h"
#include "Helper/pipe.h"
#include "headers.h"
#include <signal.h>
#include <stdlib.h>
#include "input.h"
#include <time.h>

void displayGraphicArt();

int main()
{
    /*clearFg();*/

    setPromptVar();
    loadHistory();
    makeProcessLinkedList();
    reset();

	signal(SIGINT, ctrlc);
	signal(SIGTSTP, ctrlz);
    signal(SIGCHLD, handleProcessTermination);

    displayGraphicArt();
    time_t start = time(0);

    while (1)
    {
        time_t end = time(0);
        commandTime = (int) (end - start);
        prompt();
        char* inp = input();

        start = time(0);
        addCommand(inp);

        for (char *safePtr, *token = strtok_r(inp, ";", &safePtr); token; token = strtok_r(NULL, ";", &safePtr))
            pipeIt(token);

        free(inp);
    }
    return 0;
}

void displayGraphicArt()
{
    magenta();
    printf("\n\n");

    printf(".__  .__  __                .__           .__  .__\n");
    printf("|  | |__|/  |_  ____   _____|  |__   ____ |  | |  |\n");
    printf("|  | |  \\   __\\/ __ \\ /  ___/  |  \\_/ __ \\|  | |  |\n");
    printf("|  |_|  ||  | \\  ___/ \\___ \\|   Y  \\  ___/|  |_|  |_\n");
    printf("|____/__||__|  \\___  /____  |___|  /\\___  |____/____/\n");
    printf("                   \\/     \\/     \\/     \\/\n");

    printf("\n\n\n");
    reset();
}
