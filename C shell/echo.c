//#include "echo.h"
#include "header.h"

void echo(char *tokens[]){
    if(num==1){
        printf("\n");
    }
    else{
    for(int i=1;i<num-1;i++){
        printf("%s ",tokens[i]);
    }
    printf("%s\n",tokens[num-1]);
    }
}