#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int read_bytes;	
	char buf[1024];

	if (argc == 2) {
		int fd;
		close(0);
		fd = open(argv[1], O_RDONLY);
		dup(fd);
	}
	
	while ((read_bytes = read(0, buf, sizeof (buf))) > 0) {
		write(1, buf, read_bytes);
	}

	return 0;
}
