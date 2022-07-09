#include "display.h"

void display()
{

    getcwd(cdir, sizeof(cdir));
    if (strstr(cdir, hdir))
    {
        char *path = strstr(cdir, hdir);
        path = path + strlen(hdir);
        printf("<%s@%s:~%s>", username, hostname, path);
    }
    else
    {
        printf("<%s@%s:~%s>", username, hostname, cdir);
    }
}