#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>

int main()
{
	pid_t pid;
	int i, j;

	for (j = 0; j < 10; j++) {
		
		pid = fork();

		if (0 == pid) {

			for (i = 0; i < j + 1; i++) {
				sleep(1);
				printf("\t\tchild\n");
			}
			
			exit(3);
		}
	}

	for (j = 0; j < 10; j++) {
		sleep(1);
		printf("parent\n");
	}
	return 0;
}
	
