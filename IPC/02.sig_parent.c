#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define NUMCHILD	(3)

int main()
{
	int pid, chpid[NUMCHILD];
	int i, status;

	for (i = 0; i < NUMCHILD; i++) {
		if ((pid = fork()) == 0) // process is child
			execlp("./sig_child", "./sig_child", (char*)0);
		chpid[i] = pid;
	}

	printf("sig parent : %d\n"
			"child process run\n", NUMCHILD);
	sleep(10);

	// Send SIGINT for all child process
	for (i = 0; i < NUMCHILD; i++) {
		kill(chpid[i], SIGINT);
		wait(0);
	}

	return 0;
}

