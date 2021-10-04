#include "history.h"
#include "../headers.h"
#include "../Helper/homeDir.h"
#include "../Helper/stringToNum.h"

char his[21][SIZE] = {0};
int start;
int end;

void loadHistory();
void writeHistory();

void addCommand(char* command)
{
    loadHistory();

    if (end)
        if (!strcmp(his[(end - 1) % 21], command))
            return;
        else if (his[end % 21])
        {
            strcpy(his[end % 21], strdup(command));
            ++end;
            if (start % 21 == end % 21)
                ++start;
        }
        else
        {
            strcpy(his[end % 21], strdup(command));
            ++end;
            if (start % 21 == end % 21)
                ++start;
        }
    else
        strcpy(his[end++], strdup(command));

    writeHistory();
}

void loadHistory()
{
    char path[SIZE];
    sprintf(path, "%s/.liteShell/history.txt", getHomeDir());
    FILE* fp = fopen(path, "r");

    start = 0;
    end = 0;

    size_t size = SIZE;
    char* string = malloc(size);

    if (fp)
    {
        ssize_t read;
        while (end < 21 && (read = getline(&string, &size, fp) != -1))
        {
            string[strlen(string) - 1] = 0;
            strcpy(his[end++], strdup(string));
        }
        fclose(fp);
    }
    free(string);
}

void writeHistory()
{
    char path[SIZE];
    sprintf(path, "%s/.liteShell/history.txt", getHomeDir());
    FILE* fp = fopen(path, "w");

    if (fp)
    {
        for (int i = start; i % 21 != end % 21; ++i)
            fprintf(fp, "%s\n", his[i]);

        fclose(fp);
    }
}

void printCommand(int argc, char** argv)
{
    loadHistory();
    int ct;

    ct = argc? stringToNum(argv[1]) : 10; // To print only the last 10 commands

    for (int i = end - ct + 21; i % 21 != end % 21; ++i)
        if (his[i % 21])
            printf("%s\n", his[i % 21]);
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
