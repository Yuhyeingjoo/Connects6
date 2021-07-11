#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

void *
search(DIR *dp,char *filepath){

    struct dirent *ep;
    char * path;

    while (ep = readdir (dp)){

        if(ep->d_type == DT_DIR) {

            if((strcmp(ep->d_name,".")==0)||(strcmp(ep->d_name,"..")==0)) continue;

            path=(char*)malloc(sizeof(char)*(strlen(filepath)+strlen(ep->d_name)+3));
            strcpy(path,filepath);
            //filepath = (char *)malloc(sizeof(char)*(strlen(path)+strlen(ep->d_name)));
            strcat(path,ep->d_name);
            strcat(path,"/");
            DIR *dps= opendir(path);
            printf("path = %s\n",path);
            search(dps,path);
            free(path);
        }
        puts(ep->d_name);
                
    }
}

int
main (void)
{

  DIR *dp;
  char *filepath;

  filepath="./";

  dp = opendir(filepath);

  printf("filepath =%s\n",filepath);

  if (dp != NULL)
    {
        
        search(dp,filepath);
        
      (void) closedir (dp);
    }
  else
    perror ("Couldn't open the directory");

  return 0;
}

