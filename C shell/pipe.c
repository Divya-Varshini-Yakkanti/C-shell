#include "header.h"
#include "input.h"

int tokenizepipe(char *tokens[], char *line){
    int num = 0;
  tokens[num] = strtok(line,"|");

  while (tokens[num] != NULL)
  {
    tokens[++num] = strtok(NULL,"|");
  }

  tokens[num] = NULL;

  return num;
}

void piping(char *line[]){
    char pipecmd[2000];
    int x =0;
    for(int i=0;i<num;i++){
        for(int j=0;j<strlen(line[i]);j++){
            pipecmd[x] = line[i][j];
            x++;
        }
        pipecmd[x] = ' ';
        x++;
    }
    pipecmd[x] = '\0';
    
    char *tokens[50];
    //char *line[50];
    //char *pi[50];
   
    /*for(int i=0;i<no_cmds;i++){
        for(int j=0;j<strlen)
    }*/
   
    
    //printf("%s",pipecmd);
    int no_pipes = 0;
    for (int i = 0; i < strlen(pipecmd); i++)
    {
        if (pipecmd[i] == '|')
            no_pipes++;
    }
    int no_cmds = tokenizepipe(tokens,pipecmd);
   //printf("%d %d",no_cmds,no_pipes);
    if (no_cmds != no_pipes + 1)
    {
        perror("Invalid syntax in pipe");
        return;
    }
    int fd[no_cmds - 1][2];

   
    for (int i = 0; i < no_cmds - 1; i++)
    {
        char *line[50];
        int num = tokenize(line,tokens[i]);
        /*for(int i=0;i<d;i++){
            printf("%s\n",line[i]);
        }*/
        if (pipe(fd[i]) < 0)
        {
          
            perror("Error in pipe");
        }
        if (!i)
        {
            int out = dup(STDOUT_FILENO);
            dup2(fd[i][1], STDOUT_FILENO);
            close(fd[i][1]);
            //printf("%d =num\n",num);
            input(line,num);
            dup2(out, STDOUT_FILENO);
            close(out);
        }
        else
        {
            int in = dup(STDIN_FILENO);
            int outFile = dup(STDOUT_FILENO);
            dup2(fd[i][1], STDOUT_FILENO);
            dup2(fd[i - 1][0], STDIN_FILENO);
            close(fd[i][1]);
            close(fd[i - 1][0]);
            input(line,num);
            dup2(in, STDIN_FILENO);
            dup2(outFile, STDOUT_FILENO);
            close(in);
            close(outFile);
        }
    }
    char *ln[50];
    //int d = tokenize(ln,tokens[no_cmds-1]);
    num = tokenize(ln,tokens[no_cmds-1]);
    int in = dup(STDIN_FILENO);
    dup2(fd[no_cmds - 2][0], STDIN_FILENO);
    close(fd[no_cmds - 2][0]);
    //printf("%d =num\n",num);
    input(ln,num);
    dup2(in, STDIN_FILENO);
    close(in);
    num = n;
}