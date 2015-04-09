#include <fcntl.h>
#include <sys/type.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int fd;
	int ret;
	char buff[100];

	fd = open(argv[1],  O_RDONLY);
	ret = lseek(fd, 0, SEEK_END);
	
	printf("Filesize = %d\n", ret);

	close(fd);
	return 0;
}
