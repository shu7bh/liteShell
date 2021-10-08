#include "../headers.h"
#include "changeIO.h"

int changeIO(int fd, int current)
{
    if (fd < 0)
    {
        logStdError("Bad file descriptor");
        return 0;
    }

    if (dup2(fd, current) < 0)
    {
        logError("Unable to duplicate file descriptor:");
        return 0;
    }

    if (fd != current)
        if (close(fd) == -1)
        {
            logError("close error");
            return 0;
        }
    return 1;
}
