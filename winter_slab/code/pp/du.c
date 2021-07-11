#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
int lSize;
char * archive, * target;
void direc_make(char* path){
	char *new;
	new = (char*)malloc(strlen(path));
	new = strtok(path,"/");
//	strcpy(new,"../new");
//	istrcat(new,path);
//	while(new=!NULL){
//		if(opendir(new)==NULL){
//		printf("new directory :%s\n",new);
//		mkdir(new,0777);
//		}	
//	}
	
}
char* read(char* path){
	FILE *fp ;
	char *data;
	size_t result;
	fp = 	fopen(path,"r");
	if(fp==NULL) printf("File error\n");
	fseek(fp,0,SEEK_END);
	lSize =ftell(fp);
	rewind(fp);
	data=(char*)malloc(sizeof(char)*lSize);
	result = fread(data,1,lSize,fp);
	fclose(fp);
	for(int i=0; i<lSize; i++)
	printf("datat%d\n",data[i]);
	return data;
}

void write(char* data, char * path){
	FILE *wp;
	char* ul_path;
	int path_len[1] ={ 10};
	ul_path = (char*)malloc(sizeof(char)*(strlen(path)+10));
	strcpy(ul_path,"./");
	strcat(ul_path,path);
//	strcat(ul_path,"/dat.bin");
	wp = fopen(ul_path,"wb");
//	int length = 18/sizeof(int)+1;
	fwrite(path_len,4,1,wp);
	printf("length :%d\n",lSize);
	int path_length = strlen(path);
	fwrite(data,1,lSize,wp);
	fclose(wp);
	FILE *fp,* w;
	int re[0];
	fp = fopen(ul_path,"rb");
	fread(re,4,1,fp);
	char *ul;
	ul = (char*)malloc(lSize);
	fread(ul,1,lSize,fp);
	fclose(fp);
	printf("re[1]: %s re: %d\n" , ul, re[0]);
	w = fopen("udlt","wb");
	fwrite(ul,1,lSize,w);
	fclose(w);
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
	    printf("Cur path: %s\n", path);
        if(ep->d_type == DT_DIR) {

            if((strcmp(ep->d_name,".")==0)||(strcmp(ep->d_name,"..")==0)) continue;

	    
            printf("if path = %s\n",path);
	  //  read(path);
	    puts(ep->d_name);
            strcat(path,"/");
            DIR *dps= opendir(path);
		

            search(dps,path);
            free(path);
        }
	else{
		char* else_path;
		printf("else path = %s\n",path);
		write(read(path),archive);
	       	puts(ep->d_name);
	}
                
    }
}

int
main (int argc, char ** argv)
{
	archive = (char*)malloc(strlen(argv[1]));
	if(argc==3){	
		target = (char*)malloc(strlen(argv[2])+1);
		strcpy(target,argv[2]);	
		strcat(target,"/");
	}
 	DIR *dp;
 	char *filepath;
	strcpy(archive,argv[1]);
	printf("archticv: %s,  target: %s \n", archive, target);

		
 
 	dp = opendir(target);
	if(dp==NULL){
		printf("Not open root file. \n");
		return 0;

	}

  	printf("filepath =%s\n",target);

  	if (dp != NULL)
    	{
       	 
        	search(dp,target);
        
      	(void) closedir (dp);
    	}
  	else
    		perror ("Couldn't open the directory");

  	return 0;
}

