#include "token.h"
#include "../headers.h"

int tokenize(char* inputBuffer, char** argv, int* argc, int* bgprocess)
{
    char* token;
    char* safePtr;
    token = strtok_r(inputBuffer, " \t\r", &safePtr);
    argv[0] = strdup(token);

    int flag = 0;

    if (!strcmp(argv[0], "cd"))
        flag = 1;

    *argc = 0;

    while ((token = strtok_r(NULL, " \t\r", &safePtr)))
        argv[++*argc] = strdup(token);

    if (*argc > flag && flag)
    {
        printf("Too many arguments\n");
        return 0;
    }

    if (argv[*argc][0] == '&')
        argv[(*argc)--] = 0, *bgprocess = 1;
    else
        *bgprocess = 0;

    argv[*argc + 1] = 0;

    return 1;
}
