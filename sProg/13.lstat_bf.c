#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int i;
	struct stat buf;
	char *ptr;

		for (i=1; i<argc; i++) {
			lstat(argv[i], &buf);

			if (buf.st_mode & S_IFMT == S_IFREG)
				ptr = "Regular";
			else if (buf.st_mode & S_IFMT == S_IFDIR)
				ptr = "Directory";
			else if (buf.st_mode & S_IFMT == S_IFCHR)
				ptr = "Character special";
			else if (buf.st_mode & S_IFMT == S_IFBLK)
				ptr = "Block special";
			else if (buf.st_mode & S_IFMT == S_IFIFO)
				ptr = "fifo";
			else if (buf.st_mode & S_IFMT == S_IFLNK)
				ptr = "Symbolic link";
			else if (buf.st_mode & S_IFMT == S_IFSOCK);
				ptr = "Socket";
			else
				ptr = "Unknown";

			printf("%s\n", ptr);


		}
	return 0;
}
