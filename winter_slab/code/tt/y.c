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
	new = (char*)malloc(strlen(path)+12);
//	new = strtok(path,"/");
	strcpy(new,"../extract/");
	strcat(new,path);
//	while(new=!NULL){
		if(opendir(new)==NULL){
		printf("new directory :%s\n",new);
		mkdir(new,0777);
		}	
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
void directory(char *path){
	int path_len[1];
	path_len[0] = strlen(path);
	FILE *fp;
	fp = fopen(archive,"at+");
	fwrite(path_len,4,1,fp);
	fwrite(path,1,path_len[0],fp);
	path_len[0]=0;
	fwrite(path_len,4,1,fp);
	fclose(fp);
}
void write(char* data, char * archive, char* path ){
	FILE *wp;
	char* ul_path;
	int path_len[1] ={ strlen(path)};
	int f_size[1];
	f_size[0]=lSize;
	ul_path = (char*)malloc(sizeof(char)*(strlen(archive)+10));
	strcpy(ul_path,"./");
	strcat(ul_path,archive);
	wp = fopen(ul_path,"at+");
	fwrite(path_len,4,1,wp);
	fwrite(path,1,path_len[0],wp);
	fwrite(f_size,4,1,wp);
	fwrite(data,1,lSize,wp);
	fclose(wp);
	/*
	FILE *fp,* w;
	int re[0];
	fp = fopen(ul_path,"rb");
	fread(re,4,1,fp);
	char *ul, *ul_;
	ul = (char*)malloc(path_len[0]);
	ul_ = (char*)malloc(path_len[0]+5);
	strcpy(ul_,"../");
	fread(ul,1,path_len[0],fp);
	strcat(ul_,ul);
	fclose(fp);
	printf("path: %s len: %d\n" , ul, re[0]);
	w = fopen(ul_,"wb");
	fwrite(ul_,1,strlen(ul_),w);
	fclose(w);
*/
}
void list(char *archive){
	FILE *fp, *wp;
	fp = fopen(archive,"rb");
	wp = fopen("list.bin","at+");
	while(1){
		printf("1111111111\n");
		char *cur_path, *buf, *display;
		int len_data[2];
		fread(len_data,4,1,fp);
		if(feof(fp)!=0) break;
		cur_path =(char*)malloc(len_data[0]);
		fread(cur_path,1,len_data[0],fp);
		fwrite(cur_path,1,len_data[0],wp);
		fread(len_data,4,1,fp);
		if(len_data[0]!=0){
		
		buf =(char*) malloc(len_data[0]);
		fread(buf, 1, len_data[0],fp);
		}
	}

	fclose(fp);
	fclose(wp);
}
void extract(char* name){
	FILE *fp;
	fp =fopen(name,"rb");
	while(1){
		int p_len[1], f_len[1];
		char * cur_path, *buf;
		fread(p_len,4,1,fp);
		if(feof(fp)!=0) break;
		cur_path = (char*)malloc(p_len[0]+1);
		fread(cur_path,1,p_len[0],fp);
		cur_path[p_len[0]]='\0'; 
		fread(f_len,4,1,fp);
		printf("p_len :%d f_len: %d cur:path: %s\n",p_len[0],f_len[0],cur_path);
		if(f_len[0]==0){
			direc_make(cur_path);
			printf("direc: %s\n",cur_path);	
		}
		else{
			char* ultimate;
			ultimate = (char*)malloc(strlen(cur_path)+20);
			strcpy(ultimate,"../extract/");
			strcat(ultimate, cur_path);
			printf("new file name:%s\n",ultimate);
			buf = (char*)malloc(f_len[0]);
			fread(buf,1,f_len[0],fp);
			FILE *wp;
			
			wp = fopen(ultimate,"wb");
			fwrite(buf,1,f_len[0],wp);
			fclose(wp);
		}
	}
	fclose(fp);
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
	    directory(path);
	    puts(ep->d_name);
            strcat(path,"/");
            DIR *dps= opendir(path);
		

            search(dps,path);
            free(path);
        }
	else{
		char* else_path;
		printf("else path = %s\n",path);
		write(read(path),archive,path);
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
	
	list(archive);
	extract(archive);
  	return 0;
}

