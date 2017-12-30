#include "commonHeader.h"
#include "detach_thread.h"

void *thread_function_detach(void *arg);

char message_detach[] = "hello world";
int thread_finished   = 0;


void detach_basic(){
	int result = 0;
	pthread_t one_thread;
	pthread_attr_t one_thread_attr;

	result = pthread_attr_init(&one_thread_attr);
	if(result != 0){
		perror("pthread attribute intializing failed\n");
		return;
	}

	result = pthread_attr_setdetachstate(
			&one_thread_attr,
			PTHREAD_CREATE_DETACHED);
	
	if(result != 0){
		perror("pthread set detach state failed\n");
		return;
	}

	result = pthread_create(&one_thread,&one_thread_attr,
							thread_function_detach,
							(void*)message_detach);	
	if(result != 0){
		perror("thread creation failed\n");
		return;
	}

	(void)pthread_attr_destroy(&one_thread_attr);
	while(!thread_finished){
		printf("Waiting for detached thread to stay its finished\n");
		sleep(1);
	}

	printf("Other thread finished, bye!\n");
	return;
}


void *thread_function_detach(void *arg){
	printf("thread_function is running. Argument was %s\n",(char*)arg);
	sleep(4);
	printf("second thread setting finished flag and exiting now\n");
	thread_finished = 1;
	pthread_exit(NULL);
}