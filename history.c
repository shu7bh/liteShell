#include "history.h"
#include "headers.h"
#include "stringToNum.h"

char* his[20] = {0};
int start;
int end;

void loadHistory();
void writeHistory();

void addCommand(char* command)
{
    loadHistory();

    if (end)
        if (!strcmp(his[(end - 1) % 20], command))
            return;
        else if (his[end % 20])
        {
            free(his[end % 20]);
            his[end % 20] = strdup(command);
            ++end;
            if (start % 20 == end % 20)
                ++start;
        }
        else
        {
            his[end % 20] = strdup(command);
            ++end;
            if (start % 20 == end % 20)
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
        while (end < 20 && (read = getline(&string, &size, fp) != -1))
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
        for (int i = start; i % 20 != end % 20; ++i)
            fprintf(fp, "%s\n", his[i]);

        fclose(fp);
    }
}

void printCommand(int argc, char** argv)
{
    loadHistory();
    int ct;
    if (argc)
    {
        ct = stringToNum(argv[1]);
        for (int i = end - ct + 20; i % 20 != end % 20; ++i)
            if (his[i % 20])
                printf("%s\n", his[i % 20]);
    }
    else
        for (int i = start; i % 20 != end % 20 && i < start + 10; ++i)
            printf("%s\n", his[i % 20]);
}
