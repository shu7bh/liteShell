#include "../Helper/stringToNum.h"
#include "../headers.h"
#include <sys/select.h>
#include "baywatch.h"
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


struct termios OGTermios;

void reset_terminal_mode()
{
    tcsetattr(0, TCSANOW, &OGTermios);
}

void set_conio_terminal_mode()
{
    struct termios new_termios;

    /* take two copies - one for now, one for later */
    tcgetattr(0, &OGTermios);
    memcpy(&new_termios, &OGTermios, sizeof(new_termios));

    /* register cleanup handler, and set the new terminal mode */
    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

int getch()
{
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0)
        return r;
    else
        return c;
}

void bayWatch(char** argv, int argc)
{
    if (argc > 3)
    {
        logStdError("Too many arguments");
        return;
    }

    int num = 0;
    int flag = -1;
    FILE* fin;

    for (int i = 1; i <= argc; ++i)
        if (!strcmp(argv[i], "-n"))
        {
            if (i + 1 > argc)
            {
                logStdError("Argument not provided for -n");
                return;
            }
            num = stringToNum(argv[++i]);
            if (num <= 0)
            {
                logStdError("Argument is not a number");
                return;
            }
        }
        else if (!strcmp(argv[i], "interrupt"))
            fin = fopen("/proc/interrupts", "r"), flag = 0;
        else if (!strcmp(argv[i], "newborn"))
            fin = fopen("/proc/loadavg", "r"), flag = 1;
        else if (!strcmp(argv[i], "dirty"))
            fin = fopen("/proc/meminfo", "r"), flag = 2;
        else
        {
            logStdError("Wrong argument");
            return;
        }

    if (flag < 0)
        return;

    char *str = malloc(SIZE), *safePtr, *token;
    size_t size = SIZE;
    time_t start = time(0), end;
    int ct = 0;

    while (1)
    {
        set_conio_terminal_mode();
        if (!kbhit())
        {
            reset_terminal_mode();
            end = time(0);

            if (end - start >= num)
            {
                start = end;
                char display[SIZE] = {0};

                switch (flag)
                {
                case 2:
                    for (int i = 0; i < 17; ++i)
                        getline(&str, &size, fin);

                    token = strtok_r(str, " \t\n", &safePtr); token = strtok_r(NULL, " \t\n", &safePtr);

                    sprintf(display, "%s kb", token);
                    fclose(fin);
                    fin = fopen("/proc/meminfo", "r");
                    break;
                case 1:
                    getline(&str, &size, fin);
                    token = strtok_r(str, " \t\n", &safePtr);

                    for (int i = 0; i < 4; ++i)
                        token = strtok_r(NULL, " \t\n", &safePtr);

                    strcpy(display, token);
                    fclose(fin);
                    fin = fopen("/proc/loadavg", "r");
                    break;

                case 0:
                    getline(&str, &size, fin);

                    int  i = 0;
                    for (token = strtok_r(str, " \t\n", &safePtr); token; ++i, token = strtok_r(NULL, " \t\n", &safePtr))
                        strcat(display, token), strcat(display, "\t");

                    strcat(display, "\n");

                    if (ct++)
                        memset(display, 0, SIZE);

                    for (int i = 0; i < 2; ++i)
                        getline(&str, &size, fin);

                    token = strtok_r(str, " \t\n", &safePtr);

                    for (int j = 0; j < i; ++j)
                    {
                        token = strtok_r(NULL, " \t\n", &safePtr);
                        strcat(display, token); strcat(display, "\t");
                    }

                    fclose(fin);
                    fin = fopen("/proc/interrupts", "r");
                    break;
                }
                printf("%s\n", display);
            }
            else;
        }
        else if (getch() == 'q')
            break;
    }
    fclose(fin);
    reset_terminal_mode();
    free(str);
}
