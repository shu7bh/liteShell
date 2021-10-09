#include "Features/commandAutoCompletion.h"
#include "Features/autoSuggestions.h"
#include "Features/history.h"
#include "Features/prompt.h"
#include <termios.h>
#include "headers.h"
#include <stdlib.h>
#include <ctype.h>
#include "input.h"

void die(const char *s)
{
    logError(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

void commandComplete(char* inp, int len, int* pt)
{
    for (int i = 0; i < len; ++i)
        printf("\b \b");

    printf("%s", inp);
    *pt = strlen(inp);
}

void callAutoSuggestion(char* inp, char* autoSug)
{
    strcpy(autoSug, autoSuggestions(inp));
    promptDarkGray();
    printf("%s", autoSug);
    for (int i = 0; i < strlen(autoSug); ++i)
        printf("\b");
    promptReset();
}

char* input()
{
    char *inp = malloc(SIZE);

    if (!inp)
    {
        logError("malloc error");
        return "";
    }

    char c;

    setbuf(stdout, NULL);
    enableRawMode();

    memset(inp, '\0', SIZE);
    int pt = 0;
    int prev = 0;
    int commandCompleteCt = 0;
    char autoSug[SIZE] = {0};

    while (read(STDIN_FILENO, &c, 1) == 1)
    {
        for (int i = 0; i <= strlen(autoSug); ++i)
            printf(" ");
        for (int i = 0; i <= strlen(autoSug); ++i)
            printf("\b");

        printf("\r");
        prompt();
        printf("%s", inp);

        if (!iscntrl(c))
        {
            commandCompleteCt = 0;
            inp[pt++] = c;
            printf("%c", c);

            callAutoSuggestion(inp, autoSug);
            continue;
        }
        switch(c)
        {
        case 2:
        {
            int len = strlen(inp);
            if (autoComplete(inp, &commandCompleteCt, -1))
                commandComplete(inp, len, &pt);
            callAutoSuggestion(inp, autoSug);
            break;
        }
        case 4:
            printf("\n");
            exit(0);
        case 6:
            strcat(inp, autoSug);
            printf("%s", autoSug);
            pt += strlen(autoSug);
            break;
        case 7:
            memset(inp, 0, SIZE);
            printf("\n");
            prompt();
            pt = 0;
            callAutoSuggestion(inp, autoSug);
            break;
        case 9:
        {
            int len = strlen(inp);
            if (autoComplete(inp, &commandCompleteCt, 1))
                commandComplete(inp, len, &pt);

            callAutoSuggestion(inp, autoSug);
            break;
        }
        case 10:
            break;
        case 12:
            strcpy(inp, "clear");
            break;
        case 14:
        {
            int len = strlen(inp);
            if (autoComplete(inp, &commandCompleteCt, 1))
                commandComplete(inp, len, &pt);
            callAutoSuggestion(inp, autoSug);
            break;
        }
        case 27:
        {
            char buf[3];
            buf[2] = 0;

            if (read(STDIN_FILENO, buf, 2) == 2) // length of escape code
            {
                switch (buf[1])
                {
                case 'A':
                    printf("\33[2K\r");
                    prompt();
                    memset(inp, '\0', SIZE);
                    strcpy(inp, getNextHistory(&prev));
                    printf("%s", inp);
                    pt = strlen(inp);
                    break;

                case 'B':
                    printf("\33[2K\r");
                    prompt();
                    memset(inp, '\0', SIZE);
                    strcpy(inp, getPrevHistory(&prev));
                    printf("%s", inp);
                    pt = strlen(inp);
                    break;

                case 'C':
                    strcat(inp, autoSug);
                    printf("%s", autoSug);
                    pt += strlen(autoSug);
                    break;

                default:
                    break;
                }

            }
            callAutoSuggestion(inp, autoSug);
            break;
        }
        case 127:
            commandCompleteCt = 0;
            if (pt > 0)
            {
                inp[--pt] = 0;
                printf("\b \b");
            }
            callAutoSuggestion(inp, autoSug);
            break;
        default:
            printf("%d\n", c);
            break;
        }

        if (c == 10 || c == 12)
            break;
    }
    disableRawMode();
    printf("\n");
    return inp;
}
