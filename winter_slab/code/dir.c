#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

void
search(DIR *dp,char *filepath){

    struct dirent *ep;
    char path[64], next[64];

    //printf("filepath =%s\n",filepath);

    while (ep = readdir (dp)){

        puts(ep->d_name);

        if((ep->d_name[0]=='.')||(ep->d_name[1]=='.')) continue;

        if(ep->d_type == DT_DIR) {
	    strcpy(next,filepath);
	    strcpy(path,"/");
	    strcat(next,path);
            strcat(next,ep->d_name);
	    printf("sub: %s\n",next);
            dp = opendir (next);
            search(dp,next);
        }

    }
}

int
main (void)
{

  DIR *dp;

  char *filepath;

  filepath=".";

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
