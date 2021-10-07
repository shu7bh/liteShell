#include "token.h"
#include "../headers.h"

int tokenize(char* inputBuffer, char** argv, int* argc, int* bgprocess)
{
    char* token;
    char* safePtr;
    token = strtok_r(inputBuffer, " \t\r", &safePtr);
    argv[0] = strdup(token);

    *argc = 0;

    while ((token = strtok_r(NULL, " \t\r", &safePtr)))
        argv[++*argc] = strdup(token);

    if (!strcmp(argv[*argc], "&"))
        argv[(*argc)--] = 0, *bgprocess = 1;
    else
        *bgprocess = 0;

    argv[*argc + 1] = 0;

    return 1;
}
