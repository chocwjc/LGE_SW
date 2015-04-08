#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd, fdd;

	fd = open(argv[1], O_WRONLY  | O_CREAT | O_TRUNC, 0666);
	close(1);
	dup(fd);

	printf("Hello\n");
	close(fd);

	
	return 0;
}
