#include "commonHeader.h"
#include "cancel_thread.h"

void *thread_function_cancel(void *arg);



void cancel_thread_basic(){
	
	int result = 0;
	pthread_t one_thread;
	void *thread_result = NULL;
	result = pthread_create(&one_thread,NULL,thread_function_cancel,NULL);
	if(result != 0){
		perror("pthread creation failed\n");
		return;
	}

	sleep(3);
	printf("Cancelling thread ... \n");
	result = pthread_cancel(one_thread);
	if(result != 0){
		perror("Pthread cancellation failed\n");
		return;
	}

	result = pthread_join(one_thread,&thread_result);	
	if(result != 0){
		perror("Thread join failed\n");
		return;
	}

	return;
}


void *thread_function_cancel(void *arg){
	int result = 0;
	/*
		set the cancel state of the thread
	*/
	result = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	if(result != 0){
		perror("Thread  pthread cancel state function failed\n");
		pthread_exit(0);
	}

	/*
		set the cancel type of the of the thread
	*/

	result = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
	if(result != 0){
		perror("Thread pthread set cancel type failed\n");
		pthread_exit(0);
	}

	printf("Thread function is running\n");
	for(int i = 0;i < 10;i++){
		printf("Thread is still running (%d)\n",i);
		sleep(1);
	}

	pthread_exit(0);
}