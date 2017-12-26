#include "commonHeader.h"
#include "functions.h"

char message[] = "hello world";

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