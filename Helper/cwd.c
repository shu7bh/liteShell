#include "../headers.h"
#include <unistd.h>
#include "cwd.h"

const char* getCWD()
{
    char* cwd = malloc(SIZE);
    if (!cwd)
    {
        logError("malloc error");
        return "";
    }

    getcwd(cwd, SIZE);

    return cwd;
}
