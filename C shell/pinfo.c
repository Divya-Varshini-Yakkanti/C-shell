#include "header.h"

void pinfo(char *line[])
{
    pid_t pid;

    //if (num > 1)
    if(line[1]!=NULL && line[2]==NULL)
        pid = atoi(line[1]);
    else
        pid = getpid();

    if (pid == 0)
    {
        perror("incorrect pid");
        exit(1);
    }
    else
    {
        printf("pid -- %d\n", pid);
    }

    char str1[1000];

    sprintf(str1, "/proc/%d/stat", pid);

    FILE *f1 = fopen(str1, "r");
    int plus = 0;
    int i = 1;
    char status;
    unsigned long vm;
    if (f1 == NULL)
    {
        perror("Error in opening f1");
    }
    else
    {

        char temp[1000];
        long int pgrp, tgpid;
        while (fscanf(f1, "%s", temp) == 1)
        {
            if (i == 5)
                pgrp = atoi(temp);
            if (i == 8)
                tgpid = atoi(temp);
            if (i == 23)
            {
                vm = atoi(temp);
                break;
            }
            i++;
        }
        if (tgpid == pgrp)
            plus = 1;

        fseek(f1, 0, SEEK_SET);
        fscanf(f1, "%*d %*s %c", &status);
        fclose(f1);
    }

    printf("Process Status -- {%c", status);
    if (plus == 1)
        printf("+");
    printf("}\n");
    printf("memory -- %lu Bytes {Virtual Memory}\n", vm);

    char str3[1000], temp1[1000];
    sprintf(str3, "/proc/%d/exe", pid);
    size_t s = readlink(str3, temp1, 1000);
    if (s > 0)
    {
        temp1[s] = 0;
        if (strstr(temp1, hdir))
        {
            char *path = strstr(temp1, hdir);
            path += strlen(hdir);
            printf("Executable Path -- ~%s\n", path);
        }
        else
            printf("Executable Path -- %s\n", temp1);
    }
    else
    {

        perror("Error opening str3 file");
    }
}