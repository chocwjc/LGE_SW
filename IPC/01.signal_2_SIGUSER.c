#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void handler(int signo)
{
	printf("Signal no(%d) received\n", signo);
}

int main()
{
	if (signal(SIGUSR1, handler) == SIG_ERR) {
		fprintf(stderr, "Can't set user1 signal handler\n");
		exit(1);
	}

	if (signal(SIGUSR2, handler) == SIG_ERR) {
		fprintf(stderr, "Can't set user2 signal handler\n");
		exit(1);
	}

	sleep(20);
	sleep(20);
	sleep(20);
	sleep(20);
	sleep(20);
	
	exit(0);
}

