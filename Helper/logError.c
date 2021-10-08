#include "../headers.h"
#include "logError.h"

void logError(const char* error)
{
    errorRed();
    perror(error);
    errorReset();
}

void logStdError(const char* error)
{
    errorRed();
    fprintf(stderr, "%s\n", error);
    errorReset();
}
