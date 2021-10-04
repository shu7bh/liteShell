#include "echo.h"
#include "../headers.h"

void echo(int argc, char** argv)
{
    for (int i = 0; i < argc; ++i)
        printf("%s ", argv[i + 1]);
    printf("\n");
}
