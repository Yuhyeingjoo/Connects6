#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
int lSize, sig;
char * archive, * target;
void direc_make(char* path){
	char *new;
	new = (char*)malloc(strlen(path)+12);
//	new = strtok(path,"/");
	strcpy(new,"../extract/");
	strcat(new,path);
//	while(new=!NULL){
		if(opendir(new)==NULL){
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
}
void list(char *archive){
	FILE *fp, *wp;
	fp = fopen(archive,"rb");
	wp = fopen("list.bin","at+");
	while(1){
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
	char *root;
	int root_len[1];
	fread(root_len,4,1,fp);
	root = (char*)malloc(root_len[0]+1);
	fread(root,1,root_len[0],fp);
	root[root_len[0]]='\0';
	root =strtok(root, "/");
	direc_make(root);
	rewind(fp);
	while(1){
		int p_len[1], f_len[1];
		char * cur_path, *buf, *root;
		fread(p_len,4,1,fp);
		if(feof(fp)!=0) break;
		cur_path = (char*)malloc(p_len[0]+1);
		fread(cur_path,1,p_len[0],fp);
		cur_path[p_len[0]]='\0'; 
		fread(f_len,4,1,fp);
		if(f_len[0]==0){
			direc_make(cur_path);
		}
		else{
			char* ultimate;
			ultimate = (char*)malloc(strlen(cur_path)+20);
			strcpy(ultimate,"../extract/");
			strcat(ultimate, cur_path);
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
        if(ep->d_type == DT_DIR) {

            if((strcmp(ep->d_name,".")==0)||(strcmp(ep->d_name,"..")==0)) continue;

	    
	    directory(path);
	    puts(ep->d_name);
            strcat(path,"/");
            DIR *dps= opendir(path);
		

            search(dps,path);
            free(path);
        }
	else{
		char* else_path;
		write(read(path),archive,path);
	       	puts(ep->d_name);
	}
                
    }
}

int
main (int argc, char ** argv)
{	

	if(strcmp(argv[1],"archive")==0)
		sig =0;
	else if(strcmp(argv[1],"list")==0)
		sig=1;
	else if(strcmp(argv[1],"extract")==0)
		sig= 2;
	archive = (char*)malloc(strlen(argv[2]));
	strcpy(archive,argv[2]);
	if(sig ==0){	
		target = (char*)malloc(strlen(argv[3])+1);
		strcpy(target,argv[3]);	
		strcat(target,"/");
	}
 	DIR *dp;
 	char *filepath;
		
	if(sig==0){ 
 		dp = opendir(target);
		if(dp==NULL){
			printf("Not open root file. \n");
			return 0;

		}


  		if (dp != NULL)
    		{
       	 
        		search(dp,target);
        
      		(void) closedir (dp);
    			}
  		else
    			perror ("Couldn't open the directory");
	
	}
	if(sig==1)list(archive);
	if(sig==2)extract(archive);
  	return 0;
}

