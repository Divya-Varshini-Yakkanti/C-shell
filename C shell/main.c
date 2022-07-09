#include "input.h"
#include "display.h"
#include "header.h"
#include "frgbg.h"
#include "ctrls.h"
#include "redirect.h"
#include "pipe.h"

int main()
{
    signal(SIGCHLD, finbg);
    signal(SIGTSTP, ctrlz);
    signal(SIGTSTP, ctrlc);
    signal(SIGKILL,ctrld);
     
    fileIn = dup(STDIN_FILENO);
    fileOut = dup(STDOUT_FILENO);
    shellpid = getpid();
    currfg.flag = 0;
    countpid = 0;
    nofile = 0,ispipe=0;

    getcwd(cdir, sizeof(cdir));
    strcpy(hdir, cdir);
    strcpy(predir, hdir);

    gethostname(hostname, 2000);
    getlogin_r(username, 2000);
    

    while (1)
    {
        
        display();
        fflush(stdout);
        size_t length = 40;
        char *cmnd = (char *)malloc(2000 * sizeof(char));
        
        char *commands[200];
        char *pipecmds[200];
        
        if (getline(&cmnd, &length, stdin) < 0)
        {
            printf("\n");
            return 0;
            
        }

        length = strlen(cmnd);
        cmnd[length - 1] = '\0';
        int countcmnd = tokenizesemi(commands, cmnd);
        //int no_cmnds 
        
        for (int i = 0; i < countcmnd; i++)
        {
            /*char str[50]="";
            strcpy(str,commands[i]);
            no_cmds = tokenizepipe(pipecmds,commands[i]);*/

            char *tokens[2000];
            num = tokenizespace(tokens, commands[i]);
            n = num;
             for(int i=0;i<num;i++){
                if(strcmp(tokens[i],"|")==0){
                        ispipe = 1;
                }
            }
            if (strcmp(tokens[0], "repeat") == 0)
            {
                num = num - 2;
                n = num;
                for (int i = 0; i < atoi(tokens[1]); i++)
                {

                    input(tokens + 2,num);
                }
            }
           
            else
            {   if(ispipe==1){
                piping(tokens);
                }
                else{
                input(tokens,num);
                }
            }
        }
    }
}