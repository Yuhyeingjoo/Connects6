#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

void direc_make(char* path){
	char *new;
	new = (char*)malloc(strlen(path)+10);
	strcpy(new,"./new");
	strcat(new,path);
	if(opendir(new)==NULL){
		printf("new directory :%s\n",new);
		mkdir(new,0777);
	}
}
char* read(char* path){
	FILE *fp ;
	char *data;
	size_t result;
	fp = 	fopen(path,"r");
	if(fp==NULL) printf("File error\n");
	fseek(fp,0,SEEK_END);
	int lSize =ftell(fp);
	rewind(fp);
	data=(char*)malloc(sizeof(char)*lSize);
	result = fread(data,1,lSize,fp);
	if(result!=lSize)
	fclose(fp);
	printf("write %s\n",path);
	return data;
}

void write(char* data, char * path){
	FILE *wp;
	char* ul_path;
	ul_path = (char*)malloc(sizeof(char)*(strlen(path)+10));
//	strcpy(ul_path,"./new");
	strcat(ul_path,path);
	strcat(ul_path,"/final/dat.bin");
	wp = fopen(ul_path,"at+");
	size_t length = strlen(data);
	fwrite(data,1,length,wp);
	fclose(wp);
}
void *
search(DIR *dp,char *filepath){

    struct dirent *ep;
    char * path;

    while (ep = readdir (dp)){

            path=(char*)malloc(sizeof(char)*(strlen(filepath)+strlen(ep->d_name)+3));
	    
            strcpy(path,filepath);
//	    direc_make(path);
            strcat(path,ep->d_name);

        if(ep->d_type == DT_DIR) {

            if((strcmp(ep->d_name,".")==0)||(strcmp(ep->d_name,"..")==0)) continue;

	    
            printf("path = %s\n",path);
	    read(path);
	    puts(ep->d_name);
            strcat(path,"/");
            DIR *dps= opendir(path);
		

            search(dps,path);
            free(path);
        }
	else{
		char* else_path;
		printf("path = %s\n",path);
		write(read(path),path);
	       	puts(ep->d_name);
	}
                
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

