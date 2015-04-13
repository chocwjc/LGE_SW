#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MSGSIZE	(16)

char *msg1 = "Hello, world #1";
char *msg2 = "Hello, world #2";
char *msg3 = "Hello, world #3";

int main()
{
	char inbuf[MSGSIZE+1];

	int p[2], j;

	// Create pipe, p[0] for read, p[1] for write
	if (pipe(p) < 0) {
		perror("Pipe call");
		exit(1);
	}

	// p[1] for pipe write
	write(p[1], msg1, MSGSIZE);
	write(p[1], msg2, MSGSIZE);
	write(p[1], msg3, MSGSIZE);

	// p[0] for pipe read
	for (j = 0; j < 3; j++) {
		read(p[0], inbuf, MSGSIZE);
		printf("%s", inbuf);
	}

	exit(0);
}
