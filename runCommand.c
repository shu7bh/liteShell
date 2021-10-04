#include "runCommand.h"
#include "headers.h"
#include "Features/makeChild.h"
#include "Helper/token.h"
#include "Helper/callWriitenFunctions.h"
#include <string.h>

void runCommand(char* inputBuffer)
{
    char* temp = strdup(inputBuffer);
    char** argv = malloc(SIZE);

    int* argc = malloc(sizeof(int));
    int* bgprocess = malloc(sizeof(int));
    if (!tokenize(inputBuffer, argv, argc, bgprocess))
        return;


    if (!callWrittenFunctions(argv, *argc))
    {
        if (*bgprocess)
            makeChildBg(argv);
        else
            makeChildFg(argv);
    }

    strcpy(inputBuffer, temp);

    free(temp);
    free(argc);
    free(argv);
    free(bgprocess);
}
