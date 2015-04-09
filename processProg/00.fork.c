#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t pid;
	pid = fork();
	
	if (pid != 0) {
		usleep(100);
	}

	printf("after\n");
	return 0;
}
