#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int  main()
{
	int status;

	if (fork() == 0) {
		sleep(15);
		exit(15);
	}

	wait(&status);

	if ((status & 0x7f) != 0) {
		printf("Killed by signal\n");
		printf("  Signal number: %d\n", status & 0x7f);
		if ((status & 0x80) != 0)  {
			printf("Core file generated\n");
		}
	} else {
		printf("Normal terminate\n");
		printf("  Exit status: %d\n", (status & 0xff00) >> 8);
	}

	return 0;
}
