#include<pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex;
void* print(){
	sleep(2);
	printf("thread start\n");
	pthread_mutex_lock(&mutex);
	for(int i=0; i<10; i++){
		sleep(1);
		printf("------\n");
	}
	pthread_mutex_unlock(&mutex);
}
int main() {
  char c,* b;
  char  buf[24];
  pthread_t t;
	int count =0; 
  			pthread_create(&t,0x0,print,(void*)b);
	while(c!='\n'){
		pthread_mutex_lock(&mutex);
		c = getc(stdin);
		buf[count] = c;
		count++;
		pthread_mutex_unlock(&mutex);
	}
	buf[count]=0x0;
	printf("입력: %s\n",buf);
	pthread_join(t,NULL);
}
