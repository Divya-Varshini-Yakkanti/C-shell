#include "header.h"
#include "display.h"

void frgbg(char *token[], int bg)
{

    int j = 0,count = 0;
    for (int i = 0; token[i]!=NULL; i++)
    {
        if (strcmp(token[i], ""))
        {
            token[j++] = token[i];
        }
    }
    token[j] = 0;
    pid_t pid;
    pid = fork();
    int status;

    if (pid < 0)
        perror("Failed forking");

    else if (pid == 0)
    {
        setpgid(0, 0);

        if (execvp(token[0], token) < 0)
        {
            perror("execvp failed");
            exit(1);
        }
        
    }
    else
    {
         dup2(fileOut, STDOUT_FILENO);
        dup2(fileIn, STDIN_FILENO);
        if (bg != 1)
        {
            currfg.flag = 1;
            currfg.pid = pid;

            char b[1000];
            strcpy(b, token[0]);
            for (int i = 1; i < j; i++)
            {
                strcat(b, " ");
                strcat(b, token[i]);
            }
         
            strcpy(currfg.proname, b);
            signal(SIGTTOU, SIG_IGN);
            signal(SIGTTIN, SIG_IGN);
            tcsetpgrp(0, pid);
            waitpid(pid, &status, WUNTRACED);
           
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
            
            
        }
        else

        {  
            char a[1000];
            printf("%d\n", pid);
           // count++;
            backarr[countpid].jnum = countpid + 1;
             backarr[countpid].pid = pid;
              backarr[countpid].flag = 1;
           
           strcpy(a, token[0]);
            for (int i = 1; i < j; i++)
            {
                strcat(a, " ");
                strcat(a, token[i]);
            }
         
        strcpy(backarr[countpid++].proname, a);
           // printf("countpid %d",countpid);
           
        }
    }
}

void finbg(){

   pid_t pid;
   int stat;
   pid = waitpid (-1,&stat,WNOHANG);
   
   
    if (pid > 0)
    {
        for (int i=0;i<countpid;i++)
        {
            if (backarr[i].pid==pid)
            {
                if (WIFEXITED(stat)){
                if(WEXITSTATUS(stat)==0){
                    fprintf(stderr,"\n%s with %d exited normally\n",backarr[i].proname,backarr[i].pid);
                   
                }
                else
                {
                    fprintf(stderr,"\n%s with %d exited abnormally\n",backarr[i].proname,backarr[i].pid);
                    
                }
                }
                backarr[i].flag = 0;
                display();
                fflush(stdout);
                break;
            }        
        }          
    }
    
}