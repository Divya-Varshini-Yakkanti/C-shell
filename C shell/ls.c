
#include "header.h"

int isdir(char *file)
{
    struct stat st;
    if (stat(file, &st) < 0)
    {
        return -1;
    }
    if (S_ISDIR(st.st_mode))
    {

        return 1;
    }
    else
        return 0;
}

int isfile(char *file)
{
    struct stat st;
    if (stat(file, &st) < 0)
    {
        return -1;
    }
    if (S_ISREG(st.st_mode))
    {

        return 1;
    }
    else
        return 0;
}

void list(char *path, char *file)
{
    struct tm timing;

    struct stat filestat;
    stat(path, &filestat);

    if (S_ISREG(filestat.st_mode))
        printf("-");
    else if (S_ISDIR(filestat.st_mode))
        printf("d");
    else if (S_ISSOCK(filestat.st_mode))
        printf("s");
    else if (S_ISLNK(filestat.st_mode))
        printf("l");
    else if (S_ISBLK(filestat.st_mode))
        printf("b");
    else if (S_ISCHR(filestat.st_mode))
        printf("c");

    printf("%c", ((filestat.st_mode & S_IRUSR) ? 'r' : '-'));
    printf("%c", ((filestat.st_mode & S_IWUSR) ? 'w' : '-'));
    printf("%c", ((filestat.st_mode & S_IXUSR) ? 'x' : '-'));
    printf("%c", ((filestat.st_mode & S_IRGRP) ? 'r' : '-'));
    printf("%c", ((filestat.st_mode & S_IWGRP) ? 'w' : '-'));
    printf("%c", ((filestat.st_mode & S_IXGRP) ? 'x' : '-'));
    printf("%c", ((filestat.st_mode & S_IROTH) ? 'r' : '-'));
    printf("%c", ((filestat.st_mode & S_IWOTH) ? 'w' : '-'));
    printf("%c", ((filestat.st_mode & S_IXOTH) ? 'x' : '-'));

    printf(" %ld", filestat.st_nlink);

    printf(" %s", getpwuid(filestat.st_uid)->pw_name);
    printf(" %s", getgrgid(filestat.st_gid)->gr_name);
    printf(" %ld", filestat.st_size);

    char *time = (char *)calloc(1024, sizeof(char));
    strftime(time, 1024, "%b %d %H:%M ", localtime(&filestat.st_mtime));

    printf("\t%s\t%s\n", time, file);
}

void ls(char *line[])
{
    
    getcwd(cdir, sizeof(cdir));
    //printf("%s\n",cdir);
    //printf("hey");
    int l = 0, a = 0, dir = 0, dircount = 0;
    
    char *dirplace[20] ;
    
    for (int i = 1; line[i]!=NULL && line[i]!=""; i++)
    {
        if (line[i][0] == '-')
        {
            for (int j = 1; j < strlen(line[i]); j++)
            {
                if (line[i][j] == 'l')
                    l = 1;
                else if (line[i][j] == 'a')
                    a = 1;
                else
                {
                    perror("only l and a flags are recognised");
                    return;
                }
            }
        }
        if (line[i][0] != '.' && line[i][0] != '~' && line[i][0] != '-' && strcmp(line[i],"" )!= 0)
        {
            
            dir = 1;
            strcpy(dirplace[dircount], line[i]);
            dircount++;
        }
    }
    
    //printf("dircount=%d\n",dircount);
    //printf("hey");

    DIR *dp;
    struct dirent **files;
    int nfil;

    if (strcmp(line[1], ".") == 0 )
    {
        nfil = scandir(cdir, &files, NULL, alphasort);
    }
    else if (strcmp(line[1], "..") == 0)
    {
        nfil = scandir(line[1], &files, NULL, alphasort);
    }
    else if (strcmp(line[1], "~") == 0)
    {
        nfil = scandir(hdir, &files, NULL, alphasort);
    }
    if(dircount==0 && (l==1 || a==1)){
         nfil = scandir(cdir, &files, NULL, alphasort);
    }
    if(num==1 ){
        nfil = scandir(cdir, &files, NULL, alphasort);
    }
    
    for (int i = 0; i < dircount; i++)
    {
        //printf("%s ", dirplace[i]);
         
        if (dir == 1)
        {
            //if (isdir(line[dirplace]))
            nfil = scandir(dirplace[i], &files, NULL, alphasort);
        }
        //printf("%s %d\n",line[dirplace],nfil);
        //printf("l=%d\n",l);

        //printf("hey");

        if (dir == 1 && isfile(dirplace[i]) == 1 && l == 0)
        {
            printf("%s\n", dirplace[i]);
        }

        if (dir == 1 && /*(line[i][0]!='.' && line[i][0]!='-' && line[i][0]!='~'*/ isfile(dirplace[i]) == -1 && isdir(dirplace[i]) == -1)
        {
            perror("Error in ls");
        }
        if (nfil < 0 && isfile(dirplace[i]) == 1 && l == 1)
        {
            
        
            list(dirplace[i], dirplace[i]);
        }
    }
    
    long int total=0;
    //printf("nfil=%d dircount=%d\n",nfil,dircount);
    for (int i = 0; i < nfil; i++)
    {
        
        if(dircount==0){

            if ((l == 0 && a == 0))
            {

                if (files[i]->d_name[0] != '.')
                {
                    //printf("hey");
                    printf("%s\n", files[i]->d_name);
                }
            }

            if (l == 0 && a == 1)
            {
                printf("%s\n", files[i]->d_name);
            }

            char path[2000];
            strcpy(path, cdir);
            strcat(path, "/");
            strcat(path, files[i]->d_name);
            if (l == 1 && a == 0)
            {
                if (files[i]->d_name[0] != '.')
                { struct stat ab = {0};
                   if (stat(path, &ab) == 0)total += ab.st_blocks;
        

                    list(path, files[i]->d_name);
                }
            }
            if (l == 1 && a == 1)
            {
                struct stat ab = {0};
                if (stat(path, &ab) == 0)total += ab.st_blocks;
                list(path, files[i]->d_name);
            }
        }
    }
    if(l==1 && dircount==0)printf("total=%ld\n",total/2);
    
    
    for (int j = 0; j < dircount; j++)
    {
        total =0;
        if(isdir(dirplace[j])==1){
        //printf("%s:\n",dirplace[j]);
         if (dir == 1 && isdir(dirplace[j])==1)
        {
            //if (isdir(line[dirplace]))
            nfil = scandir(dirplace[j], &files, NULL, alphasort);
            if(dircount>=2){
            printf("%s:\n",dirplace[j]);
            }
        }
        for (int i = 0; i < nfil; i++)
        {

            if ((l == 0 && a == 0 && isdir(dirplace[j]) == 1))
            {

                if (files[i]->d_name[0] != '.')
                {
                    //printf("hey");
                    printf("%s\n", files[i]->d_name);
                }
            }

            if (l == 0 && a == 1)
            {
                printf("%s\n", files[i]->d_name);
            }

            char path[2000];

            if (dir == 0)
                strcpy(path, cdir);
            else
            {
                strcpy(path, dirplace[j]);
            }
            if (isdir(dirplace[j]) == 1)
            {
                strcat(path, "/");
                strcat(path, files[i]->d_name);
            }

            if (l == 1 && a == 0)
            {
                if (files[i]->d_name[0] != '.')
                {   struct stat ab = {0};
                   if (stat(path, &ab) == 0)total += ab.st_blocks;

                    list(path, files[i]->d_name);
                }
            }
            if (l == 1 && a == 1)
            {   struct stat ab = {0};
                if (stat(path, &ab) == 0)total += ab.st_blocks;
                list(path, files[i]->d_name);
            }
        }
        if(l==1&&dircount>0)printf("total=%ld\n",total/2);
    }
    }
}