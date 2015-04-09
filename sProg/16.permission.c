#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int i;
	struct stat stat;
	const char *rwx = "rwx";
	char perm[10];
	
	strcpy(perm, "---------");

	lstat(argv[1], &stat);
	
	for (i = 8; i >=0; i--) {
		if (stat.st_mode & (1UL << i)) {
			perm[9-i] = rwx[(8-i)%3];
		}
	}
	printf("%s\n", perm);
	return 0;
}
