#include "token.h"
#include "headers.h"

int tokenize(char* inputBuffer, char** argv, int* argc, int* bgprocess)
{
    char* token;
    token = strtok_r(inputBuffer, " \t\r", &inputBuffer);
    argv[0] = token;

    int flag = 0;

    if (!strcmp(argv[0], "cd"))
        flag = 1;

    *argc = 0;

    while ((token = strtok_r(inputBuffer, " \t\r", &inputBuffer)))
        argv[++*argc] = token;

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
