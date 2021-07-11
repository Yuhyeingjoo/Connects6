#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<dirent.h>
int main(){
	FILE *p, *f; 
	p=fopen("./iii/int.bin","rb");
	if(p==NULL)printf("File error.\n");
	if(opendir("./iii")==NULL){
		printf("not\n");
		return 0;
	}


	f= fopen("./iii/iee.bin","wb");
	char* arr;
	fseek(p,0,SEEK_END);
	int lSize= ftell(p);
	arr = (char*) malloc(lSize);
	rewind(p);
	printf("lsize: %d\n",lSize);
	fread(arr,1,lSize,p);
	fwrite(arr,1,lSize,f);

	fclose(p);
	fclose(f);
	return 0;
}
