#include <stdio.h>
#include <stdlib.h>

int main () {
	FILE * pFile;
	long lSize;
	char * buffer;
	size_t result;

	pFile = fopen ( "ex.txt" , "rb" );
	if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);

	buffer = (char*) malloc (sizeof(char)*lSize);
	if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

	

	FILE * wp;
	wp= fopen("wr.txt","wb");
	for(int i=0; i<lSize+5; i=i+5){
		result = fread (buffer,1,5,pFile);
		if (result != 5) {
			printf("error:%ld    %ld\n",lSize, result);
		}
	
	
		fwrite(buffer,sizeof(char),result,wp);
	}

	FILE *fp;
	fp = fopen("char.txt","rb");
	fseek(fp,0,SEEK_END);
	lSize = ftell(fp);
	rewind(fp);

	for(int i=0; i<lSize+5; i=i+5){
		result = fread(buffer,1,5,fp);
		fwrite(buffer,1,result,wp);
	}


 	free (buffer);
  	fclose (pFile);

	fclose(wp);
	return 0;
}
