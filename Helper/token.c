#include "../headers.h"
#include "token.h"

int tokenize(char* inputBuffer, char** argv, int* argc, int* bgprocess)
{
    char* token;
    char* safePtr;
    token = strtok_r(inputBuffer, " \t\r", &safePtr);
    argv[0] = strdup(token);

    if (!argv[0])
    {
        logError("strdup error");
        return 0;
    }


    *argc = 0;

    while ((token = strtok_r(NULL, " \t\r", &safePtr)))
    {
        argv[++*argc] = strdup(token);

        if (!argv[*argc])
        {
            logError("strdup error");
            return 0;
        }

    }

    if (!strcmp(argv[*argc], "&"))
        argv[(*argc)--] = 0, *bgprocess = 1;
    else
        *bgprocess = 0;

    argv[*argc + 1] = 0;

    return 1;
}
