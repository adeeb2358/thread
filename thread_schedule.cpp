#include "commonHeader.h"
#include "thread_schedule.h"

void *thread_function_sched(void *arg);
char message_sched[] = "Hello World!";
int sched_thread_finished = 0;

void sched_basic(){
	
	int result = 0;
	pthread_t one_thread;
	void *one_thread_result;
	pthread_attr_t one_thread_attr;

	int max_thread_priority;
	int min_thread_priority;
	struct sched_param scheduling_value;
	
	/*
		initializing pthread attribute 
	*/

	result = pthread_attr_init(&one_thread_attr);
	if(result != 0){
		perror("Thread attribute init failed\n");
		return;
	}

	/*
		setting the scheduling policy
	*/

	result = pthread_attr_setschedpolicy(&one_thread_attr,SCHED_OTHER);
	if(result != 0){
		perror("Thread scheduling policy set failed\n");
		return;
	}

	/*
		setting the thread behaviour,
		here its detachable thread
	*/

	result = pthread_attr_setdetachstate(&one_thread_attr,PTHREAD_CREATE_DETACHED);
	if(result != 0){
		perror("Setting detached attribute failed\n");
		return;
	}

	/*
		creating the thread with all the parameters set above
	*/

	result = pthread_create(&one_thread,&one_thread_attr,thread_function_sched,(void *)message_sched);	
	if(result != 0){
		perror("Pthread create failed\n");
		return;
	}

	max_thread_priority             = sched_get_priority_max(SCHED_OTHER);
	min_thread_priority             = sched_get_priority_min(SCHED_OTHER);
	scheduling_value.sched_priority = min_thread_priority;

	/*
		setting the priority of the created thread
	*/

	result = pthread_attr_setschedparam(&one_thread_attr,&scheduling_value);
	if(result != 0){
		perror("Setting schedule policy failed\n");
		return;
	}

	/*
		destrioy the thread attribute 
	*/

	(void) pthread_attr_destroy(&one_thread_attr);
	while(!sched_thread_finished){
		printf("waiting for the thread to finish\n");
		sleep(1);
	}

	printf("Other thread finished\n");
	return;
}

void *thread_function_sched(void *arg){
	printf("thread function is running,Argument was %s\n",(char*)arg);
	sleep(4);
	printf("Second thread setting finished flag, and exiting now \n");
	sched_thread_finished = 1;
	pthread_exit(NULL);
}