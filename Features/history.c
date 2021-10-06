#include "history.h"
#include "../headers.h"
#include "../Helper/homeDir.h"
#include "../Helper/stringToNum.h"

const int hNum = 10001;
char his[10001][SIZE] = {0};
int start = 0;
int end = 0;

void loadHistory();
void writeHistory();

void addCommand(char* command)
{
    loadHistory();

    if (end)
        if (!strcmp(his[(end - 1) % hNum], command))
            return;
        else if (his[end % hNum])
        {
            strcpy(his[end % hNum], command);
            ++end;
            if (start % hNum == end % hNum)
                ++start;
        }
        else
        {
            strcpy(his[end % hNum], command);
            ++end;
            if (start % hNum == end % hNum)
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

    if (!fp)
        return;

    size_t size = SIZE;
    char* string = malloc(size);
    ssize_t read;

    while (end < hNum && (read = getline(&string, &size, fp) != -1))
    {
        string[strlen(string) - 1] = 0;
        strcpy(his[end++], string);
    }

    fclose(fp);
    free(string);
}

void writeHistory()
{
    char path[SIZE];
    sprintf(path, "%s/.liteShell/history.txt", getHomeDir());
    FILE* fp = fopen(path, "w");

    if (fp)
    {
        for (int i = start; i % hNum != end % hNum; ++i)
            fprintf(fp, "%s\n", his[i]);

        fclose(fp);
    }
    else
    {
        logError("fopen error");
        return;
    }
}

void printCommand(int argc, char** argv)
{
    loadHistory();
    int ct;

    ct = argc? stringToNum(argv[1]) : 10; // To print only the last 10 commands

    for (int i = end - ct + hNum; i % hNum != end % hNum; ++i)
        if (his[i % hNum])
            printf("%s\n", his[i % hNum]);
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
