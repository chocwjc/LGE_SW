#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void catchint(int signo)
{
	printf("SIGINT receive\n");
}

int main()
{
	// CTRL_C - SIGINT(2) 
	signal(SIGINT, catchint);

	printf("Sleep call #1\n"); sleep(3);
	printf("Sleep call #2\n"); sleep(3);
	printf("Sleep call #3\n"); sleep(3);
	printf("Sleep call #4\n"); sleep(3);
	printf("Sleep call #5\n"); sleep(3);
	printf("Exiting\n");
	exit(0);
}

