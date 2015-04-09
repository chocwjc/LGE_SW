#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main()
{
	pid_t pid;
	pid = fork();
	if (pid > 0) {
		printf("parent : after\n");
	} else if (pid == 0)
		printf("child : after\n");
	else {
		perror("fork");
	}

	return 0;
}
