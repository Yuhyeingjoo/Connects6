./a.c           0???&V  !       ../new./ ???          !       ./k/..  ?"???  p???&V  !       ../new./k/ ??          !       ./k/.   ????          !       ../new./k/ ??          !       ../new./        ????&V  !       ../new./k/ ??          !       ./k/ii/.. ???  0???&V  !       ../new./k/ii/           !       ./k/ii/. ???          !       ../new./k/ii/           !       ./k/ii/q.txt   ????&V  !       ../new./k/ii/           !       11
??  ?"???  ????&V  !       ../new./k/ii/q.txt      !       ../new./k/ ??  0???&V  !       ./k/ooo/.. ??  P???&V  !       ../new./k/ooo/          !       ./k/ooo/. ???          !       ../new./k/ooo/          A      #include <stdio.h>
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

            if((strcmp(ep->d_name,".")==0)||(strcmp(ep->d_name,"..")==0)) co