#include "cwd.h"
#include "../headers.h"
#include <unistd.h>

const char* getCWD()
{
    char* cwd = malloc(SIZE);
    getcwd(cwd, SIZE);

    return cwd;
}
