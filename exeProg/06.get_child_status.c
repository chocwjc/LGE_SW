#include <stdio.h>
#include <unistd.h>

int main()
{
	int status;

	if (fork() == 0) {
		exit(18);
	}
	
	wait(&status);
	printf("High 8bit: 0x%02X\n", (status&0xff00)>>8);
	printf("Low  8bit: 0x%02X\n", (status&0xff));

	return 0;
}
