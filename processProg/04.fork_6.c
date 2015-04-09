#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

void my_sig(int signo)
{
	printf("my_sig(%d)\n", signo);
	wait(0);
}

int main()
{
	int i;
	pid_t pid;
	
	pid = fork();
	if (pid == 0) {
		for (i = 0; i < 3; i++) {
			sleep(1);
			printf("\t\tchild\n");
		}
		exit(3);
	}
	
	signal(SIGCHLD, my_sig);

	for (i = 0; i < 8; i++) {
		sleep(1);
		printf("parent\n");
	}
	return 0;
}

