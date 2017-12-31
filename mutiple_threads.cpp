#include "commonHeader.h"
#include "multiple_threads.h"

void *multiple_thread_function(void *arg);
#define MAX_THREAD_COUNT 6

void multiple_threads_basic(){
	int result = 0;
	pthread_t thread_array[MAX_THREAD_COUNT];
	void *thread_result;
	
	/*
		creating lot of threads
	*/
	for(int lots_of_threads = 0; lots_of_threads < MAX_THREAD_COUNT; lots_of_threads++){
		int temp = lots_of_threads;
		result = pthread_create(&(thread_array[lots_of_threads]),NULL,multiple_thread_function,(void*)&temp);
		if(result != 0){
			perror("thread creation failed\n");
			return;
		}
		sleep(1);
	}
	/*
		joining lots of threads
	*/


	printf("Waiting for thread to finish\n");
	for(int lots_of_threads = MAX_THREAD_COUNT-1; lots_of_threads >= 0;lots_of_threads--){
		result = pthread_join(thread_array[lots_of_threads],&thread_result);
		if(result == 0){
			printf("Picked up a thread\n");

		}else{
			perror("Thread join failed\n");
		}
	}

	printf("All done \n");

	return;
}


void *multiple_thread_function(void *arg){
	int my_number = *(int *)arg;
	int rand_num;
	printf("Thread function is running Argument was %d \n",my_number);
	rand_num=1+(int)(9.0*rand()/(RAND_MAX+1.0));
	sleep(rand_num);
	printf("Bye from %d\n",my_number);
	//sleep(1);
	pthread_exit(NULL);
}