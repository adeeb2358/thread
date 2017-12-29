#include "commonHeader.h"
#include "semaphore_functions.h"

//binary semaphore variable
sem_t bin_sem;

#define WORK_SIZE 1024

char work_area[WORK_SIZE];


void *sem_thread_function(void *arg){
	sem_wait(&bin_sem);
	while(strncmp("end",work_area,3) != 3){
		printf("You end Input %ld characters\n",strlen(work_area)-1);
		sem_wait(&bin_sem);
	}
	pthread_exit(NULL);
}

void semaphore_basic(){
	int result;
	pthread_t one_thread;
	void *thread_result;//return data from the thread
	result = sem_init(&bin_sem,0,0);
	
	if(result != 0){
		perror("Semaphore initialization failed\n");
		exit(EXIT_FAILURE);
	}

	result = pthread_create(&one_thread,NULL,sem_thread_function,NULL);
	if(result != 0){
		perror("Thread Creation Failed");
		exit(EXIT_FAILURE);
	}

	printf("Input Text and type 'end' to finish\n");
	while(strncmp("end",work_area,3) != 0){
		fgets(work_area,WORK_SIZE,stdin);
		sem_post(&bin_sem);
	}

	printf("Waiting for thread to finish\n");
	result = pthread_join(one_thread,&thread_result);	
	if(result != 0){
		perror("Thread join failed\n");
		exit(EXIT_FAILURE);
	}

	printf("Thread joined\n");
	sem_destroy(&bin_sem);
	exit(EXIT_SUCCESS);

	return;
}