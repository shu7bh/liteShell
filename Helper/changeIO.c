#include "changeIO.h"
#include "../headers.h"

int changeIO(int fd, int current)
{
    if (fd < 0)
    {
        perror("open error");
        return 0;
    }

    if (dup2(fd, current) < 0)
    {
        perror("Unable to duplicate file descriptor.");
        return 0;
    }

    if (fd != current)
        close(fd);
    return 1;
}
