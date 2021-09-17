#include "callWriitenFunctions.h"
#include "headers.h"
#include "cd.h"
#include "ls.h"
#include "cwd.h"
#include "pinfo.h"
#include "echo.h"
#include "repeat.h"
#include <stdlib.h>

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

