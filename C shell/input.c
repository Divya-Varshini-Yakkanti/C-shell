#include "header.h"
#include "cd.h"
#include "echo.h"
#include "pwd.h"
#include "frgbg.h"
#include "ls.h"
#include "pinfo.h"
#include "jobs.h"
#include "ctrls.h"
#include "redirect.h"
#include "pipe.h"

int tokenizespace(char *tokens[], char *line){
    int num = 0;

  tokens[num] = strtok(line," \t\n");

  while (tokens[num] != NULL)
  {
    tokens[++num] = strtok(NULL," \t\n");
  }

  tokens[num] = NULL;

  return num;
}
int tokenize(char *tokens[], char *line){
    int num = 0;

  tokens[num] = strtok(line," ");

  while (tokens[num] != NULL)
  {
    tokens[++num] = strtok(NULL," ");
  }

  tokens[num] = NULL;

  return num;
}

int tokenizesemi(char *tokens[], char *line){
    int num = 0;
  tokens[num] = strtok(line,";");

  while (tokens[num] != NULL)
  {
    tokens[++num] = strtok(NULL,";");
  }

  tokens[num] = NULL;

  return num;
}



void input(char *line[], int no){
    int bg = 0,t=0;
    for (int i = 0; line[i]!=NULL; i++)
        {
            if (!strcmp(line[i], "&"))
            {
                bg = 1;
                line[i] = "";
                break;
            }
        }
        
        char *new[500];
        
        for(int i=0;line[i]!=NULL;i++){
           
          new[i] = (char *)malloc(100 * sizeof(char));
            strcpy(new[i],line[i]);
             //new[i][strlen(line[i])-1] = '\0';
            if(strcmp(new[i], "<")==0 || strcmp(new[i], ">")==0 || strcmp(new[i], ">>")==0 ){
                   t = 1;
            }
        }
         if (t==1)
        {
            
            redirect(new,line,no);

            if(nofile ==1){
                return;
            }
            
            for (int i = 0; line[i]!=NULL; i++)
            {
                if (!strcmp(line[i], ">") || !strcmp(line[i], ">>") || !strcmp(line[i], "<"))
                {
                    perror("Invalid Syntax");
                    return;
                }
            }
          
        }
    
        if(strcmp(line[0],"cd")==0){
            cd(line);
        }
        else if(strcmp(line[0],"echo")==0){
            echo(line);
        }
        else if(strcmp(line[0],"pwd")==0){
            pwd();
        }
        else if(strcmp(line[0],"ls")==0){
            //printf("hey");
            ls(line);
        }
        else if(strcmp(line[0],"pinfo")==0){
            //printf("hey");
            pinfo(line);
        }
        else if(strcmp(line[0],"jobs")==0){
            //printf("countpid %d",countpid);
            jobs(line);
        }
        else if(strcmp(line[0],"fg")==0){
            fg(line);
        }
        else if(strcmp(line[0],"bg")==0){
             bkg(line);
        }
        else if(strcmp(line[0],"sig")==0){
             sig(line);
        }
        else{
                frgbg(line,bg);
            
        }
         dup2(fileIn, STDIN_FILENO);
        dup2(fileOut, STDOUT_FILENO);
}