#include "../Helper/homeDir.h"
#include "../headers.h"
#include "prompt.h"

int commandTime = 0;

void setPromptVar()
{
    setHomeDirVar();
}

void prompt()
{
    printf("\r");
    char cwd[SIZE];
    char varPrompt[SIZE];
    if (!getcwd(cwd, sizeof(cwd)))
    {
        logError("getcwd() error");
        return;
    }

    if (!strcmp(cwd, getHomeDir()))
        sprintf(varPrompt, "~");
    else if (strstr(cwd, getHomeDir()))
        sprintf(varPrompt, "~%s", cwd + strlen(getHomeDir()));
    else
        sprintf(varPrompt, "%s", cwd);

    char* p = strrchr(varPrompt, '/');

    if (p && strcmp(p, varPrompt))
    {
        char temp[SIZE];
        strcpy(temp, p + 1);
        memset(varPrompt, 0, SIZE);
        strcpy(varPrompt, temp);
    }

    char timePrompt[SIZE] = {0};
    if (commandTime)
    {
        if (commandTime > 60)
            sprintf(timePrompt, "took %dm%ds ", commandTime / 60, commandTime % 60);
        else
        sprintf(timePrompt, "took %ds ", commandTime);
    }

    cPrompt();
    printf("%s ", varPrompt);
    yellow();
    printf("%s", timePrompt);
    red();
    printf(" ");
    reset();

    reset();
}
