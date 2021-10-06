#include "ls.h"
#include "../Helper/homeDir.h"
#include "../headers.h"
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void SearchDir(int a_flag, int l_flag, const char* dir, int dirCt);
void printStats(const char* dir, const char* name);
void colors(const char* fullName);

int ls(int argc, char** argv)
{
    int a_flag = 0, l_flag = 0;
    int dirCt = 0;

    const char *dirs[1000];

    for (int i = 1; i < argc + 1; ++i)
        if (argv[i][0] == '-' && strlen(argv[i]) > 1)
            for (int j = 1; j < strlen(argv[i]); ++j)
                switch (argv[i][j])
                {
                    case 'a': a_flag = 1; break;
                    case 'l': l_flag = 1; break;
                    default: return -1;
                }
        else if (!strcmp(argv[i], "~"))
            dirs[dirCt++] = getHomeDir();
        else
        {
            if (argv[i][strlen(argv[i]) - 1] == '/' && argv[i][strlen(argv[i])] > 1)
                argv[i][strlen(argv[i]) - 1] = 0;
            dirs[dirCt++] = argv[i];
        }

    if (!dirCt)
        dirs[dirCt++] = ".";

    int flag = 0;

    for (int i = 0; i < dirCt; ++i)
    {
        struct dirent *directory;
        DIR *d = opendir(dirs[i]);

        if (!d)
        {
            if (access(dirs[i], F_OK) != 0)
            {
                char error[1000];
                sprintf(error, "ls: cannot access '%s'", dirs[i]);
                perror(error);
                ++flag;
                continue;
            }
        }
        else
            closedir(d);
    }

    for (int i = 0; i < dirCt; ++i)
    {
        struct dirent *directory;
        DIR *d = opendir(dirs[i]);

        if (!d)
        {
            if (access(dirs[i], F_OK) == 0)
                SearchDir(a_flag, l_flag, dirs[i], dirCt), ++flag;
        }
        else
            closedir(d);
    }

    if (flag)
        printf("\n");

    for (int i = 0; i < dirCt; ++i)
    {
        struct dirent *directory;
        DIR *d = opendir(dirs[i]);

        if (d)
        {
            SearchDir(a_flag, l_flag, dirs[i], dirCt);
            closedir(d);
        }
    }

    return 0;
}

void SearchDir(int a_flag, int l_flag, const char* dir, int dirCt)
{
    struct dirent *directory;
    DIR *d = opendir(dir);

    if (d)
    {
        struct stat statInfo;
        lstat(dir, &statInfo);

        unsigned int block = 0;
        while ((directory = readdir(d)))
        {
            if (!a_flag && directory->d_name[0] == '.') continue;
            char name[1000];
            sprintf(name, "%s/%s", dir, directory->d_name);
            lstat(name, &statInfo);
            block += statInfo.st_blocks;
        }

        if (dirCt > 1)
            printf("%s:\n", dir);
        if (l_flag)
            printf("total %u\n", block);

        closedir(d);
        d = opendir(dir);
        while ((directory = readdir(d)) != NULL)
            if (!l_flag)
            {
                if (!a_flag && directory->d_name[0] == '.')
                    continue;

                char fullName[1000];
                sprintf(fullName, "%s/%s", dir, directory->d_name);

                colors(fullName);
                printf("%s   ", directory->d_name);
                reset();
            }
            else
            {
                if (!a_flag && directory->d_name[0] == '.')
                    continue;

                char fullName[1000];
                sprintf(fullName, "%s/%s", dir, directory->d_name);

                printStats(fullName, directory->d_name);
            }
        if (!l_flag)
            printf("\n");
        closedir(d);
    }
    else if (l_flag)
        printStats(dir, dir);
    else
    {
        colors(dir);
        printf("%s\n", dir);
        reset();
    }
    if (dirCt > 1 && !l_flag)
        printf("\n");
}

void colors(const char* fullName)
{
    struct stat statInfo;
    lstat(fullName, &statInfo);

    if (S_ISLNK(statInfo.st_mode))
        magenta();
    else if (S_ISDIR(statInfo.st_mode))
        blue();
    else
        yellow();
}

void printStats(const char* fullName, const char* name)
{
    struct stat statInfo;
    lstat(fullName, &statInfo);

    colors(fullName);

    printf((S_ISLNK(statInfo.st_mode)) ? "l" : (S_ISDIR(statInfo.st_mode))? "d" : "-");
    printf((statInfo.st_mode & S_IRUSR) ? "r" : "-");
    printf((statInfo.st_mode & S_IWUSR) ? "w" : "-");
    printf((statInfo.st_mode & S_IXUSR) ? "x" : "-");
    printf((statInfo.st_mode & S_IRGRP) ? "r" : "-");
    printf((statInfo.st_mode & S_IWGRP) ? "w" : "-");
    printf((statInfo.st_mode & S_IXGRP) ? "x" : "-");
    printf((statInfo.st_mode & S_IROTH) ? "r" : "-");
    printf((statInfo.st_mode & S_IWOTH) ? "w" : "-");
    printf((statInfo.st_mode & S_IXOTH) ? "x" : "-");

    printf("  %4ld", statInfo.st_nlink);
    struct group *grp = getgrgid(statInfo.st_gid);
    printf("  %15s", getpwuid(statInfo.st_uid)->pw_name);

    if (grp)
        printf("  %15s", getgrgid(statInfo.st_gid)->gr_name);
    else
        printf("  %15u", statInfo.st_gid);

    printf("  %7ld", statInfo.st_size);

    struct tm time_last, time_present;
    char time_val[256];

    time_t present = time(0);

    localtime_r(&statInfo.st_mtime, &time_last);
    localtime_r(&present, &time_present);

    if (time_last.tm_year == time_present.tm_year)
        strftime(time_val, sizeof(time_val), "%b %e %H:%M", localtime(&statInfo.st_mtime));
    else
        strftime(time_val, sizeof(time_val), "%b %e %Y", localtime(&statInfo.st_mtime));

    printf("  %s ", time_val);
    printf("  %s\n", name);

    reset();
}
