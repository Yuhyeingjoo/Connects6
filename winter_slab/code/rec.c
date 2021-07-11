#include<string.h>
#include<stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>



  struct dirent *ep;

  DIR *dp;

void search(struct dirent *ep, char _path []){
        char  path[64];
        struct dirent* dir_;
        DIR *dir;
	char cur_path[64];
	strcpy(cur_path,_path);
        if(ep->d_type==DT_DIR&& ep->d_name[0]!='.'){
		strcpy(path,"/");
		strcat(_path,path);
                strcat(_path,ep->d_name);
	       	dir = opendir(_path);
		
                if(dir!=NULL){
                        while(dir_ = readdir(dir)){
                               	printf("%s\n",dir_->d_name);
                                search(dir_,_path);
                                search(dir_,cur_path);
                		printf("sub: %s\n",_path);
                        }
                }
        }
}
int
main (void)
{
  dp = opendir ("./");
  if (dp != NULL)
    {
      while (ep = readdir (dp)){
        char root[64]; 
	strcpy(root,".");
        puts (ep->d_name);
        search(ep,root);
      }
      (void) closedir (dp);
    }
  else
    perror ("Couldn't open the directory");

  return 0 ;

}

