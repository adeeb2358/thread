#include "commonHeader.h"
#include "functions.h"
#include "semaphore_functions.h"
#include "mutex_functions.h"
#include "detach_thread.h"
#include "thread_schedule.h"
#include "cancel_thread.h"
int main(){
	int start_s = clock();
	
	//thread_caller();
	//busy_wait_basic();
	//semaphore_basic();
	//mutex_basic();
	//detach_basic();
	//sched_basic();
	cancel_thread_basic();
	int a = 0;
	int stop_s = clock();
	std::cout <<"\nExecutionTime:- " <<  (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;
	std::cout <<"\nPress enter key to exit\n";
	int ch = std::cin.get();	
	return 0;
}