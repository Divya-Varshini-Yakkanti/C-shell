//#include "pwd.h"
#include "header.h"

void pwd(){
    if(getcwd(cdir,sizeof(cdir))){
        printf("%s\n",cdir);
    }
    else{
        perror("Error in pwd");
    }
}