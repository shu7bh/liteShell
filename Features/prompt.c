#include "prompt.h"
#include "../Helper/homeDir.h"
#include "../headers.h"
#include "../Helper/colors.h"

char name[33], hostname[60], lprompt[1000], cwd[1000];
void setPromptVar()
{
    setHomeDirVar();
    getlogin_r(name, 32);
    gethostname(hostname, sizeof(hostname));
    sprintf(lprompt, "<%s@%s:", name, hostname);
}

void prompt()
{
    char varPrompt[500];
    if (getcwd(cwd, sizeof(cwd)))
    {
        if (!strcmp(cwd, getHomeDir()))
            sprintf(varPrompt, "~");
        else if (strstr(cwd, getHomeDir()))
            sprintf(varPrompt, "~%s", cwd + strlen(getHomeDir()));
        else
            sprintf(varPrompt, "%s", cwd);

        cPrompt();
        printf("%s%s> ", lprompt, varPrompt);
        reset();
    }
    else
        perror("getcwd() error");
}
