#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int fd;
	int ret, cur;
	char buff[100];

	fd = open(argv[1],  O_RDONLY);
	cur = lseek(fd, 0, SEEK_CUR);
	ret = lseek(fd, 0, SEEK_END);
	lseek(fd, cur, SEEK_SET);

	printf("Filesize: %d\n", ret);

	close(fd);
	return 0;
}
