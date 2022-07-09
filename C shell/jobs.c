#include "header.h"

void bsort(pro list[], int s)
{
    int i, j;
    pro temp;
    
    for (i = 0; i < s - 1; i++)
    {
        for (j = 0; j < (s - 1-i); j++)
        {
            if(strcmp(list[j].proname,list[j+1].proname)>0)
            {
                temp = list[j];
               
                list[j] = list[j + 1];
                
                list[j + 1] = temp;
            } 
        }
    }
}


void jobs(char *tokens[])
{
    int count = 0;
    /*if (num > 2)
    {
        perror("Error in number of arguments");
    }*/
    /*if(tokens[2]!=NULL){
        perror("Error in number of arguments");
    }*/
    //printf("%d",countpid);
    //qsort(backarr->proname,countpid,sizeof(char*),cmpstr);
    bsort(backarr,countpid);
    for (int i = 0; i < countpid; i++)
    {
        if (backarr[i].flag == 1)
        {
            char str1[100];

            sprintf(str1, "/proc/%d/stat", backarr[i].pid);
            FILE *f1 = fopen(str1, "r");
           // count++;
            char status;
            if (f1 != NULL)
            {
                char Process_state[50] = "Running";
                fseek(f1, 0, SEEK_SET);
                fscanf(f1, "%*d %*s %c", &status);
                fclose(f1);

                if (status == 'T' || status == 't')
                {
                    //printf("hey\n");
                    strcpy(Process_state, "Stopped");
                }
                //if (num == 1)
                if(tokens[1]!=NULL && strcmp(tokens[1],"")==0)
                {
                    printf("[%d] %s %s [%d]\n", backarr[i].jnum, Process_state, backarr[i].proname, backarr[i].pid);
                }
                else if(tokens[1]==NULL){
                    printf("[%d] %s %s [%d]\n", backarr[i].jnum, Process_state, backarr[i].proname, backarr[i].pid);
                }
                //else if(num==2)
                else if (strcmp(tokens[1],"")!=0 && tokens[1]!=NULL)
                {
                    if (tokens[1][1] == 'r' && strcmp(Process_state, "Running") == 0)
                    {
                        printf("[%d] %s %s [%d]\n",backarr[i].jnum , Process_state, backarr[i].proname, backarr[i].pid);
                    }
                    if (tokens[1][1] == 's' && strcmp(Process_state, "Stopped") == 0)
                    {
                        printf("[%d] %s %s [%d]\n", backarr[i].jnum, Process_state, backarr[i].proname, backarr[i].pid);
                    }
                }
            }
            else
            {
                backarr[i].flag = 0;
            }
        }
    }
}

void fg(char *tokens[])
{
    if (num != 2)
    {
        perror("Invalid number of arguments");
    }

    int index = 0, found = 0, status;
    int jnum = atoi(tokens[1]);
    for (int i = 0; i < countpid; i++)
    {
        if (backarr[i].flag == 1)
        {
            index++;

            if (index == jnum)
            {
                found = 1;
                if (kill(backarr[i].pid, SIGCONT) < 0)
                {
                    perror("Error in kill");
                }
                

                currfg.pid = backarr[i].pid;
                strcpy(currfg.proname, backarr[i].proname);
                currfg.flag = 1;
                backarr[i].flag = 0;

                signal(SIGTTOU, SIG_IGN);
                signal(SIGTTIN, SIG_IGN);
                tcsetpgrp(0, backarr[i].pid);
                waitpid(backarr[i].pid, &status, WUNTRACED);

                tcsetpgrp(0, shellpid);

                signal(SIGTTOU, SIG_DFL);
                signal(SIGTTIN, SIG_DFL);
                if(WIFSTOPPED(status)){
                strcpy(backarr[countpid].proname,currfg.proname);
                backarr[countpid].pid = currfg.pid;
                backarr[countpid].flag = 1;
                backarr[countpid].jnum = countpid + 1;
                //backarr[countpid].jnum++;
                countpid++;
                
            }
                break;
            }
        }
    }

    if (found == 0)
    {
        perror("No such background process with given jnum exists");
    }
}

void bkg(char *tokens[])
{
    if (num != 2)
    {
        perror("Invalid number of arguments");
    }

    int index = 0, found = 0, status;
    int jnum = atoi(tokens[1]);
    for (int i = 0; i < countpid; i++)
    {
        if (backarr[i].flag == 1)
        {
            index++;

            if (index == jnum)
            {
                found = 1;
                if (kill(backarr[i].pid, SIGTTIN) < 0)
                {
                    perror("Error in kill");
                    return;
                }
                if (kill(backarr[i].pid, SIGCONT) < 0)
                {
                    perror("Error in kill");
                    return;
                }

                break;
            }
        }
    }

    if (found == 0)
    {
        perror("No such background process with given jnum exists");
    }
}

void sig(char *tokens[])
{
    if (num != 3)
    {
        perror("Invalid number of arguments");
    }

    int index = 0, found = 0, status;
    int jnum = atoi(tokens[1]);
    int signum = atoi(tokens[2]);
    for (int i = 0; i < countpid; i++)
    {
        if (backarr[i].flag == 1)
        {
            //index++;

            if (backarr[i].jnum== jnum)
            {
                
                if (kill(backarr[i].pid, signum ) < 0)
                {
                    perror("Error in kill");
                    return;
                }
                else{
                    backarr[i].flag = 0;
                    found = 1;
                }
               

                break;
            }
        }
    }

    if (found == 0)
    {
        perror("No such background process with given jnum exists");
    }
}