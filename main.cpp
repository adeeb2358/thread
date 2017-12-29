#include "commonHeader.h"
#include "functions.h"
#include "semaphore_functions.h"

int main(){
	int start_s = clock();
	
	//thread_caller();
	//busy_wait_basic();
	semaphore_basic();
	int a = 0;
	
	int stop_s = clock();
	std::cout <<"\nExecutionTime:- " <<  (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000;
	std::cout <<"\nPress enter key to exit\n";
	int ch = std::cin.get();	
	return 0;
}