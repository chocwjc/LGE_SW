#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h> //new
#include <sys/types.h> // new
#include <unistd.h> // new

/* The direct structure */
#if 0
struct dirent {
	ino_t          d_ino;       /* inode number */
	off_t          d_off;       /* not an offset; see NOTES */
	unsigned short d_reclen;    /* length of this record */
	unsigned char  d_type;      /* type of file; not supported
																 by all filesystem types */
	char           d_name[256]; /* filename */
};
#endif 

// 1. directory traversal 을 모듈화, chdir() 사용
// 2. directory traversal 동안 dir 을 만나면 재귀 호출할수 있도록
void my_ls(char *dname)
{
	DIR *dp;
	struct dirent *p;
	struct stat stat;

	chdir(dname);
	dp = opendir(".");

	while ((p =  readdir(dp)) != NULL)  {
		
		// directory entry name 으로 lstat
		lstat(p->d_name, &stat);
		printf("%s\n", p->d_name);

		if (S_ISDIR(stat.st_mode))  {
			if (strcmp(p->d_name, ".")  && strcmp(p->d_name, ".."))
				my_ls(p->d_name);
		}
	}
	closedir(dp);
	chdir("..");
}

int main(int argc, char **argv)
{
	my_ls(argv[1]);
	return 0;
}
