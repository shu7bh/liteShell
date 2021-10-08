#include "../headers.h"
#include <unistd.h>
#include "cwd.h"

const char* getCWD()
{
    char* cwd = malloc(SIZE);
    getcwd(cwd, SIZE);

    return cwd;
}
