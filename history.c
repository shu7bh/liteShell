#include "history.h"
#include "headers.h"
#include "stringToNum.h"

char* his[21] = {0};
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
            free(his[end % 21]);
            his[end % 21] = strdup(command);
            ++end;
            if (start % 21 == end % 21)
                ++start;
        }
        else
        {
            his[end % 21] = strdup(command);
            ++end;
            if (start % 21 == end % 21)
                ++start;
        }
    else
        his[end++] = strdup(command);

    writeHistory();
}

void loadHistory()
{
    FILE* fp = fopen("history.txt", "r");

    start = 0;
    end = 0;

    size_t size = 1000;
    char* string = malloc(size);

    if (fp)
    {
        ssize_t read;
        while (end < 21 && (read = getline(&string, &size, fp) != -1))
        {
            string[strlen(string) - 1] = 0;
            his[end++] = strdup(string);
        }
        fclose(fp);
    }
    free(string);
}

void writeHistory()
{
    FILE* fp = fopen("history.txt", "w");

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

    ct = argc? stringToNum(argv[1]) : 10;

    if (argc)
    {
        for (int i = end - ct + 21; i % 21 != end % 21; ++i)
            if (his[i % 21])
                printf("%s\n", his[i % 21]);
    }
    else
        for (int i = end - 1; i >= 0 && i + 11 != end; --i)
            if (his[i % 21])
                printf("%s\n", his[i % 21]);
}
