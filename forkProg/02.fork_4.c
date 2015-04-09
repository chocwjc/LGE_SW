#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	int i;

	pid = fork();
	
	// child
	if (pid == 0) {
		for (i=0; i<3; i++)  {
			sleep(1);
			printf("\t\tchild\n");
		}
		exit(3);
	}
	wait(0);
	printf("parent\n");
	return 0;
}
