#include<stdio.h>

int main(){
	FILE *fp;
	int c[100];
	fp = fopen("ex.txt","r");
	int k = fread(c,sizeof(int),100,fp);
	for(int i=0; i<100; i++){
			
		printf("%d\n",c[i]);
	}
}
