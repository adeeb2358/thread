#include "commonHeader.h"
#include "functions.h"

char message[] = "hello world";
int run_now    = 1;

void *my_thread_function1(void *argument_list){
	int print_count = 0;
	while(print_count++ < 20){
		if(run_now == 2){
			printf("2");
			run_now = 1;
		}else{
			sleep(1);
		}
	}
	printf("my_thread_function1 is running\n");
}

void *my_thread_function(void *argument_list){
	printf("my_thread_function is running\n");
	sleep(3);
	strcpy(message,"Bye!");
	pthread_exit(const_cast<char *>("Thank you for the CPU time"));
}

void thread_caller(){
	int result;
	pthread_t one_thread;
	void *thread_result;
	result = pthread_create(&one_thread,NULL,my_thread_function,(void*)message);
	if(result != 0){
		perror("Thread Creation failed");
		exit(EXIT_FAILURE);
	}

	printf("Waiting thread to finish\n");
	result = pthread_join(one_thread,&thread_result);
	if(result != 0){
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}

	printf("Thread Joined, it returned \n:==%s\n",(char*)thread_result);
	printf("The message is now %s\n",message);
	return;
}


void busy_wait_basic(){
	int result;
	int print_count = 0;
	pthread_t one_thread;
	result = pthread_create(&one_thread,NULL,my_thread_function1,NULL);

	while(print_count++ < 20){
		if(run_now == 1){
			printf("1");
			run_now = 2;
		}else{
			sleep(1);
		}
	}

	printf("Waiting thread to finish\n");
	result = pthread_join(one_thread,NULL);
	if(result != 0){
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}

	return;
}


