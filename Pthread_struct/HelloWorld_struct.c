#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Global vaiable : accessible to  all  threads */
int thread_count;
/* User type */
typedef struct __pthd{
	long rank;
	long value;
}PCB;

/* Thread function */
void *Hello(void* pass){
	PCB *param = pass;
	long my_rank = param -> rank;
	long value = param -> value;
	printf("Hello from thread %ld of %d and value is %ld \n", my_rank , thread_count , value);
	return NULL;
}

int main(int argc , char* argv[]){
	long thread;
	pthread_t *thread_handles;
	/* Get number of threads from command line */
	thread_count = strtol(argv[1] , NULL , 10);
	
	thread_handles = malloc(thread_count*sizeof(pthread_t));
	
	for(thread = 0;thread < thread_count ; thread++){
		PCB *pth_param = malloc(sizeof(PCB));
		pth_param -> rank = thread;
		pth_param -> value = thread * 2;
		pthread_create(&thread_handles[thread] , NULL , Hello , (void*)pth_param);	
	}
	printf("Hello from the main thread\n");
	
	for(thread = 0; thread < thread_count ; thread++)
		pthread_join(thread_handles[thread] , NULL);
		
	free(thread_handles);
	return 0;
}
