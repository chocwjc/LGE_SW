#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int i;
	struct stat buf;
	char *ptr;

		for (i=1; i<argc; i++) {
			lstat(argv[i], &buf);

			if (S_ISREG(buf.st_mode))
				ptr = "Regular";
			else if (S_ISDIR(buf.st_mode))
				ptr = "Directory";
			else if (S_ISCHR(buf.st_mode))
				ptr = "Character special";
			else if (S_ISBLK(buf.st_mode))
				ptr = "Block special";
			else if (S_ISFIFO(buf.st_mode))
				ptr = "fifo";
			else if (S_ISLNK(buf.st_mode))
				ptr = "Symbolic link";
			else if (S_ISSOCK(buf.st_mode))
				ptr = "Socket";
			else
				ptr = "Unknown";

			printf("%s\n", ptr);


		}
	return 0;
}
