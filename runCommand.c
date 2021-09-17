#include "runCommand.h"
#include "headers.h"
#include "makeChild.h"
#include "token.h"
#include "repeat.h"
#include "cd.h"
#include "ls.h"
#include "cwd.h"
#include "pinfo.h"
#include "echo.h"
#include <stdlib.h>
#include <string.h>

int callWrittenFunctions(char**, int);

void runCommand(char* inputBuffer)
{
    char** argv = malloc(10001);

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

    free(argc);
    free(argv);
    free(bgprocess);
}

int callWrittenFunctions(char** argv, int argc)
{
    int present = 1;
    if (!strcmp(argv[0], "cd"))
        if (cd(argv[1]))
            perror("cd error");
        else;
    else if (!strcmp(argv[0], "echo"))
        echo(argc, argv);
    else if (!strcmp(argv[0], "pwd"))
        printf("%s\n", getCWD());
    else if (!strcmp(argv[0], "exit"))
        exit(0);
    else if (!strcmp(argv[0], "ls"))
        ls(argc, argv);
    else if (!strcmp(argv[0], "repeat"))
        repeat(argc, argv);
    else if (!strcmp(argv[0], "pinfo"))
        pinfo(argc, argv);
    else
        present = 0;
    return present;
}
