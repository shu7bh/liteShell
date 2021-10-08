#include "../headers.h"
#include "homeDir.h"
#include "cwd.h"

const char* homeDir;

void setHomeDirVar()
{
    homeDir = getCWD();
}

const char* getHomeDir()
{
    return homeDir;
}
