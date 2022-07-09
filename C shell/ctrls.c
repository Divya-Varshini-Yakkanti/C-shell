#include "header.h"
#include "display.h"

/*void ctrlz(int sgno)
{

    if (getpid() != shellpid)
        return;

    if (currfg.flag == 1)
    {
        if (kill(currfg.pid, SIGTTIN) < 0)
        {
            perror("Error in kill");
            return;
        }
        if (kill(currfg.pid, SIGTSTP) < 0)
        {
            perror("Error in kill");
            return;
        }

        backarr[countpid].flag = 1;
        backarr[countpid].pid = currfg.pid;
        strcpy(backarr[countpid++].proname, currfg.proname);
        currfg.flag = 0;

        return;
    }

    signal(SIGTSTP, ctrlz);
}

void ctrlc(int sig_num)
{
    if (getpid() != shellpid)
        return;

    if (currfg.flag == 1)
    {
        if (kill(currfg.pid, SIGINT) < 0)
        {
            perror("Error in kill");
        }
        currfg.flag = 0;
    }
    else
    {
        perror("no foreground process");
        fflush(stdout);
        display();
    }
    signal(SIGINT, ctrlc);

    fflush(stdout);
    return;
}*/
void ctrlz(int signo){
     printf("\n");
    display();
    fflush(stdout);
}
void ctrlc(int signo){
     printf("\n");
    display();
    fflush(stdout);
}
void ctrld(int signo){
     printf("\n");
    display();
    fflush(stdout);
}