#ifndef __HEADER_H
#define __HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <signal.h>

char username[2000];
char hostname[2000];
char hdir[2000];
char cdir[2000];
char predir[2000];

int num,fileIn,fileOut,n;
int nofile,ispipe;
int countpid;

typedef struct process pro;
struct process{
    pid_t pid;
    char proname[100];
    int flag;
    int jnum;  
};
char *line1[1000];
pro backarr[1024];
pro currfg;
pid_t shellpid;



#endif