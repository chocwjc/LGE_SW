#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MSGSIZE 20

int main()
{
	int fd[2], pid;
	char msgout[MSGSIZE] = "Hello, world\n";
	char msgin[MSGSIZE];

	// Make a pipe
	if (pipe(fd) < 0) {
		perror("Failed to pipe()");
		exit(1);
	}

	// Make a child process
	if ((pid = fork()) > 0) {
		/* Parent process */

		// Parent do write only 
		close(fd[0]);
		write(fd[1], msgout, MSGSIZE);
	} else if (pid == 0) {
		
		/* Child process */
		// Child do read only
		close(fd[1]);
		read(fd[0], msgin, MSGSIZE);
		puts(msgin);
	} else {
		perror("Failed to fork()");
		exit(2);
	}

	wait(0);

	return 0;
}
		
