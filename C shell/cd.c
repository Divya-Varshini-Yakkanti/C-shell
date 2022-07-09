//#include "cd.h"
#include "header.h"

void cd(char *line[]){
    getcwd(cdir,sizeof(cdir));
    /*if(line[2]!=NULL){
            perror("Error in number of arguments");
    }*/
    if(line[1]==NULL  || strcmp(line[1],"~")==0 ){
        
        if(chdir(hdir)==-1){
            perror("Error in changing directory");
        }
        else{
        strcpy(predir,cdir);
        }
    }
    else if(strstr(line[1],"~")){
       
        char *temp = line[1];
        temp++;
        if(strcmp(temp,username)==0){
            if(chdir(hdir)==-1){
            perror("Error in changing directory");
        }
        }
       else{
            perror("Error in changing directory");
        }
         strcpy(predir,cdir);
    }
    else if(strcmp(line[1],"-")==0){
        if(strcmp(cdir,hdir)==0){
            perror("pwd not set");
        }else{
        printf("%s\n",predir);
        }
        if(chdir(predir)==-1){
            perror("Error in changing directory");
        }
        else{
        strcpy(predir,cdir);
        }
    }
    else{
         
        if(chdir(line[1])==-1){
            perror("Error in changing directory");
        }
        else{
        strcpy(predir,cdir);
        }

    }
}