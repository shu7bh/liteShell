#include "../Helper/stringToNum.h"
#include "../Helper/homeDir.h"
#include "../headers.h"
#include "history.h"

const int hNum = 10001;
char his[10002][SIZE] = {0};
int start = 0;
int end = 0;

void writeHistory();

void addCommand(char* command)
{
    loadHistory();

    if (end)
        if (!strcmp(his[(end - 1)], command))
            return;
        else
        {
            strcpy(his[end++], command);
            if (end == hNum)
                ++start;
        }
    else
        strcpy(his[end++], command);

    writeHistory();
}

void loadHistory()
{
    char path[SIZE];
    sprintf(path, "%s/.liteShell/history.txt", getHomeDir());
    FILE* fp = fopen(path, "r");

    start = 0;
    end = 0;

    if (!fp)
        return;

    size_t size = 0;
    char* string = 0;

    while (getline(&string, &size, fp) != -1)
    {
        string[strcspn(string, "\n")] = 0;
        strcpy(his[end++], string);
    }

    fclose(fp);
    if (string)
        free(string);
}

void writeHistory()
{
    char path[SIZE];
    sprintf(path, "%s/.liteShell/history.txt", getHomeDir());
    FILE* fp = fopen(path, "w");

    if (fp)
    {
        for (int i = start; i != end; ++i)
            fprintf(fp, "%s\n", his[i]);

        fclose(fp);
    }
    else
    {
        logError("fopen error");
        return;
    }
}

void printCommand(char** argv, int argc)
{
    loadHistory();
    int ct;

    ct = argc? stringToNum(argv[1]) : 10; // To print only the last 10 commands

    if (ct < 0)
    {
        logStdError("Give a number greater than 0");
        return;
    }

    for (int i = end < ct? 0 : end - ct; i != end; ++i)
        if (his[i])
            printf("%s\n", his[i]);
}

char* getNextHistory(int* prev)
{
    loadHistory();

    if (end > *prev)
        return his[end - ++(*prev)];

    return his[end - *prev];
}

char* getPrevHistory(int* prev)
{
    loadHistory();

    if (*prev >= 2)
        return his[end - --(*prev)];
    else if (*prev >= 1)
        --(*prev);

    return "";
}
