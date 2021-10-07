#include "callWriitenFunctions.h"
#include "../headers.h"
#include "../Features/cd.h"
#include "../Features/ls.h"
#include "../Features/pinfo.h"
#include "../Features/echo.h"
#include "../Features/repeat.h"
#include "../Features/history.h"
#include "../Features/jobs.h"
#include "../Features/sigs.h"
#include "../Features/fg.h"
#include "../Features/bg.h"
#include "../Features/replay.h"
#include "linkedList.h"
#include "cwd.h"
#include <stdlib.h>

int callWrittenFunctions(char** argv, int argc)
{
    int present = 1;
    if (!strcmp(argv[0], "cd"))
        cd(argv, argc);
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
    else if (!strcmp(argv[0], "history"))
        printCommand(argc, argv);
    else if (!strcmp(argv[0], "jobs"))
        jobs(argv, argc);
    else if (!strcmp(argv[0], "sig"))
        sig(argv, argc);
    else if (!strcmp(argv[0], "fg"))
        fg(argv, argc);
    else if (!strcmp(argv[0], "bg"))
        bg(argv, argc);
    else if (!strcmp(argv[0], "replay"))
        replay(argv, argc);
    else
        present = 0;
    return present;
}
