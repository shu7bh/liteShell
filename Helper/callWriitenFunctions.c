#include "callWriitenFunctions.h"
#include "../Features/history.h"
#include "../Features/replay.h"
#include "../Features/repeat.h"
#include "../Features/pinfo.h"
#include "../Features/echo.h"
#include "../Features/jobs.h"
#include "../Features/sigs.h"
#include "../Features/cd.h"
#include "../Features/ls.h"
#include "../Features/fg.h"
#include "../Features/bg.h"
#include "../headers.h"
#include "linkedList.h"
#include <stdlib.h>
#include "cwd.h"

int callWrittenFunctions(char** argv, int argc, int bgFlag)
{
    int present = 1;
    if (!strcmp(argv[0], "cd"))
        cd(argv, argc);
    else if (!strcmp(argv[0], "echo"))
        echo(argv, argc);
    else if (!strcmp(argv[0], "pwd"))
        printf("%s\n", getCWD());
    else if (!strcmp(argv[0], "exit"))
        exit(0);
    else if (!strcmp(argv[0], "ls"))
        ls(argv, argc);
    else if (!strcmp(argv[0], "repeat"))
        repeat(argv, argc, bgFlag);
    else if (!strcmp(argv[0], "pinfo"))
        pinfo(argv, argc);
    else if (!strcmp(argv[0], "history"))
        printCommand(argv, argc);
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
