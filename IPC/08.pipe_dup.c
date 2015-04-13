#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int fd[2], pid;

	if (pipe(fd) < 0) {
		perror("pipe() failed");
	}

	if ((pid = fork()) == 0) {
		close(fd[1]);
		dup2(fd[0], 0);
		execlp(argv[2], argv[2], (char*)0);
	}

	close(fd[0]);
	dup2(fd[1], 1);
	execlp(argv[1], argv[1], (char*)0);
}
