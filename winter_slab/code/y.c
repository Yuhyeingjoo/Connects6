#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
char * archive, *target;
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
void direc_make(char* path){
	char *new;
	new = (char*)malloc(strlen(path)+1);
	strcpy(new,path);
	if(opendir(new)==NULL){
		printf("new dir %s\n",new);
		mkdir(new,0777);
	}
}
void write(void* data){
	FILE *wp;
	char *archive_name;
	int pathSize[0];
	direc_make(target);
	archive_name = (char*)malloc(strlen(archive)+strlen(target)+1);
	strcpy(archive_name,target);
	strcat(archive_name,"/");
	strcat(archive_name,archive);
	wp = fopen(archive_name,"at+");
	size_t length = strlen(data);
	pathSize[0]= strlen(archive_name);
	fwrite(pathSize,4,1,wp);
	fclose(wp);
}
void *
search(DIR *dp,char *filepath){

    struct dirent *ep;
    char * path;

    while (ep = readdir (dp)){

            path=(char*)malloc(sizeof(char)*(strlen(filepath)+strlen(ep->d_name)+3));
	    
            strcpy(path,filepath);
            strcat(path,ep->d_name);

        if(ep->d_type == DT_DIR) {

            if((strcmp(ep->d_name,".")==0)||(strcmp(ep->d_name,"..")==0)) continue;

            //filepath = (char *)malloc(sizeof(char)*(strlen(path)+strlen(ep->d_name)));
	    
           // printf("path = %s\n",path);
	    read(path);
	    puts(ep->d_name);
            strcat(path,"/");
            DIR *dps= opendir(path);
		

            search(dps,path);
            free(path);
        }
	else{
		
		//printf("path = %s\n",path);
		write(read(path));
	       	puts(ep->d_name);
	}
                
    }
}

int
main (int argc ,char **argv)
{
  
  archive = (char*)malloc(strlen(argv[1]));
  strcpy(archive,argv[1]);
  if(argc==3){
  	target = (char*)malloc(strlen(argv[2]));
	strcpy(target,argv[3]);
  } 


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

