#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_THREADS 10

void *print_hello_world(void *tid){
	long id;
	id = (long)tid;
	fprintf(stderr, "Hello World. Greetings from thread %ld\n",id);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
	pthread_t threads[NUMBER_OF_THREADS];
	int status;
	long i;
	for(i = 0; i < NUMBER_OF_THREADS; i++){
		printf("Main here. Creating thread %d\n",i);
		status = pthread_create(&threads[i],NULL,print_hello_world, (void *)i);
		if ( status != 0 ){
			printf("Oops. pthread create returned error code %d\n",status);
			exit(-1);
		}
	}
	exit(0);
}
