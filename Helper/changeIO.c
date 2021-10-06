#include "changeIO.h"
#include "../headers.h"

int changeIO(int fd, int current)
{
    if (fd < 0)
    {
        printf("Bad file descriptor\n");
        return 0;
    }

    if (dup2(fd, current) < 0)
    {
        logError("Unable to duplicate file descriptor:");
        return 0;
    }

    if (fd != current)
        close(fd);
    return 1;
}
