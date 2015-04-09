#include <sys/type.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <tie=me.h>

// -rw-r--r-- 1 root root 149 Nov 21 05:23
int main(int argc, char **argv)
{
	struct stat buf;
	struct passwd *pwd;
	struct group *grp;

	char perm[11] = "-----------";
	char rwx[] = "rwx";

	int i;
	lstat(argv[i], &buf);

	if (S_ISDIR(buf.st_mode))
		perm[0] = 'd';
	if (S_ISCHR(buf.st_mode))
		perm[0] = 'c';
	if (S_ISBLK(buf.st_mode))
		perm[0] = 'b';
	if (S_ISSOCK
