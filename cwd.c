#include "cwd.h"
#include "headers.h"
#include <unistd.h>

const char* getCWD()
{
    char* cwd = malloc(1000);
    getcwd(cwd, 1000);

    return cwd;
}
