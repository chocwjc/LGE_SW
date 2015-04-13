#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int i;
	int fd[2], pid;

	if (pipe(fd) < 0) {
		perror("pipe() failed");
	}

	for (i = 1; i < argc; i++) {

		sleep(1);
		if ((pid = fork()) == 0) {

			if (i != 1) dup2(fd[0], 0);
			if (i != argc-1) dup2(fd[1], 1);
			execlp(argv[i], argv[i], (char*)0);
		}

	}
	sleep(2);
}
