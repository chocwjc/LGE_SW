#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXBUFF (1024)
/* Client function */
void client(int readfd, int writefd)
{
	char buff[MAXBUFF];
	int n;

	// 1) Read filename from stdin
	if (fgets(buff, MAXBUFF, stdin) == NULL) {
		printf("client(): filename read error");
	}

	n = strlen(buff);
	if (buff[n-1] == '\n')
		n--;

	// 2) Send filename to server 
	if (write(writefd, buff, n) != n) {
		printf("client(): filename write error");
	}

	// 3) Read data from server 
	while ((n = read(readfd, buff, MAXBUFF)) > 0) {

		// 4) Write it to stdout
		if (write(1, buff, n) != n) {
			printf("client(): data write error");
		}

	}

	if (n < 0) 
		printf("client(): data read error");
}

void server(int readfd, int writefd)
{
	char buff[MAXBUFF];
	int n, fd;
	extern int errno;

	// 1) get filename from clinent
	if ((n = read(readfd, buff, MAXBUFF)) <= 0)
		printf("server(): filename read error");
	buff[n] = '\0';

	// 2) open file received name
	if ((fd = open(buff, 0)) < 0) {
		strcat(buff, " cannot open\n");
	}
	n = strlen(buff);

	// 3) send file name
	if (write(writefd, buff, n) != n) {
		printf("server(): errmsg write error");
	} else {

		// 4)  Send  file content to client
		while ((n = read(fd, buff, MAXBUFF)) > 0) {

			if (write(writefd, buff, n) != n) {
				printf("server(): data write error");
			}
		}
	}
}

int main(void)
{
	//  client --> pipe1[1] pipe1[0] --> server
	//  server --> pipe2[1] pipe2[0] --> client
	int childpid, pipe1[2], pipe2[2];

	// open 2 pipe
	if (pipe(pipe1) < 0 || pipe(pipe2) < 0) {
		printf("pipe() error");
	}

	childpid = fork();
	if (childpid > 0) {
		// parent 
		close(pipe1[0]);
		close(pipe2[1]);
		client(pipe2[0], pipe1[1]);
		while (wait((int*)0) != childpid);
		close(pipe1[1]);
		close(pipe2[0]);
	} else {
		// child
		close(pipe1[1]);
		close(pipe2[0]);
		server(pipe1[0], pipe2[1]);
		close(pipe1[0]);
		close(pipe2[1]);
	}
	return 0;
}
