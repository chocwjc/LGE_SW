#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <grp.h> // new

/* The group structure.	 */
/*
	 struct group
	 {
	 char *gr_name;		// Group name.
	 char *gr_passwd;		// Password.
	 __gid_t gr_gid;		// Group ID.
	 char **gr_mem;		// Member list.
	 };
 */
int main(int argc, char **argv)
{
	int i;
	struct stat stat;
	struct group *grp;

	lstat(argv[1], &stat);

	// getgrgid() - gid 를 받고 group 구조체의 주소를 반환한다.
	grp = getgrgid(stat.st_gid);
	printf("%-*s \n", 10, grp->gr_name);

	return 0;
}


