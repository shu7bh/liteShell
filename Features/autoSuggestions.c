#include "autoSuggestions.h"
#include "../Helper/homeDir.h"
#include "../headers.h"
#include "history.h"

char* autoSuggestions(char* inp)
{
    if (!inp)
        return 0;

    char path[SIZE];
    sprintf(path, "%s/%s", getHomeDir(), ".liteShell/history.txt");

    FILE* fp = fopen(path, "r");

    if (!fp)
        return NULL;

    int ct = 1;
    while (end - ct >= 0 && strncmp(his[end - ct], inp, strlen(inp)))
        ++ct;

    return his[end - ct] + strlen(inp);
}
