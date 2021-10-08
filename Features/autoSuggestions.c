#include "../Helper/homeDir.h"
#include "autoSuggestions.h"
#include "../headers.h"
#include "history.h"

char* autoSuggestions(char* inp)
{
    if (!inp || !end)
        return 0;

    int ct = 1;
    while (end - ct >= 0 && strncmp(his[end - ct], inp, strlen(inp)))
        ++ct;

    return his[end - ct] + strlen(inp);
}
