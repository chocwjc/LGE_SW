#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/* The executable name - sig_child */
void sig_handler(int signo)
{
	printf("Child get signal (%d) - die\n", signo);
}

int main()
{
	signal(SIGINT, sig_handler);
	pause();
}

