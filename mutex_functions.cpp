#include "commonHeader.h"
#include "mutex_functions.h"

void *thread_function(void *arg);
pthread_mutex_t work_mutex;/*protects both work area and time to exit*/

#define WORK_SIZE_NEW 1024
char work_area_new[WORK_SIZE_NEW];
int time_to_exit = 0;

void mutex_basic(){
	
	int result = 0;
	pthread_t one_thread;
	void *thread_result;

	/*
		section for initializing the mutex
	*/
	
	result = pthread_mutex_init(&work_mutex,NULL);
	if(result != 0){
		perror("Mutex initialization failed\n");
		return;
	}

	result = pthread_create(&one_thread,NULL,thread_function,NULL);
	if(result != 0){
		perror("Thread creation failed\n");
		return;
	}
	
	pthread_mutex_lock(&work_mutex);
	printf("Enter some text.Enter 'end' to finish\n");
	while(!time_to_exit){
		fgets(work_area_new,WORK_SIZE_NEW,stdin);
		pthread_mutex_unlock(&work_mutex);
		while(1){
			pthread_mutex_lock(&work_mutex);
			if(work_area_new[0]!= '\0'){
				pthread_mutex_unlock(&work_mutex);
				sleep(1);
			}else{
				break;
			}
		}		
	}

	pthread_mutex_unlock(&work_mutex);
	printf("Waiting for thread to finish\n");
	result = pthread_join(one_thread,&thread_result);
	if(result != 0){
		perror("Thread join failed\n");
		return;
	}

	printf("Thread joined\n");
	pthread_mutex_destroy(&work_mutex);
	return;
}

void *thread_function(void *arg){
	
	sleep(1);
	pthread_mutex_lock(&work_mutex);
	
	while(strncmp("end",work_area_new,3) != 0){
		printf("You entered %ld characters\n",strlen(work_area_new)-1);
		work_area_new[0] = '\0';
		pthread_mutex_unlock(&work_mutex);
		sleep(1);
		pthread_mutex_lock(&work_mutex);
		while(work_area_new[0] == '\0'){
			pthread_mutex_unlock(&work_mutex);
			sleep(1);
			pthread_mutex_lock(&work_mutex);
		}
	}

	time_to_exit     = 1;
	work_area_new[0] = '\0';
	pthread_mutex_unlock(&work_mutex);
	pthread_exit(0);
}