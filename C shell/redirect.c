#include "header.h"

void redirect(char *tokens[],char *line[],int no){
    int t1=0,t2=0,t3=0;
    for(int i=0;i<no;i++){
        if(strcmp(tokens[i],"<")==0){
             t1=1;
            
        }
         if(strcmp(tokens[i],">")==0){
             t2=1;
            
        }
         if(strcmp(tokens[i],">>")==0){
             t3=1;
            
        }
    }
    if(t1==1){
         
             int f1;
        for (int i = 0;i<no; i++)
        {
            if (!strcmp(line[i], "<"))
            {
                f1 = open(line[i + 1], O_RDONLY);

                if (f1 < 0)
                {
                    nofile = 1;
                    perror("Error opening input file");
                    return;
                }
                else
                {
                    dup2(f1, STDIN_FILENO);
                    close(f1);
                }
                line[i] = "";
                line[i + 1] = "";
                break;
            }
        }
    }
    if(t2==1 || t3==1){
        
        int f2;
        for (int i = 0;i<no; i++)
        {
            if (!strcmp(line[i], ">") || !strcmp(line[i], ">>"))
            {
                if (!strcmp(line[i], ">>"))
                {
                    f2 = open(line[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                }
                else
                {
                    f2 = open(line[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                }

                if (f2 < 0)
                {
                    nofile = 1;
                    perror("Error opening output file");
                }
                else
                {
                    dup2(f2, STDOUT_FILENO);
                    close(f2);
                }
                line[i] = "";
                line[i + 1] = "";
               
                break;
            }
        }
    
    }

}