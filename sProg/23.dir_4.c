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
// 3. 2path 로 구현, 처음엔 filename 들, 그후에는 directory 재귀 traversal
void my_ls(char *dname)
{
	DIR *dp;
	struct dirent *p;
	struct stat stat;

	printf("%s:\n", dname);
	chdir(dname);
	dp = opendir(".");

	while ((p =  readdir(dp)) != NULL)  {
		// directory entry name 으로 lstat
		printf("\t%s\n", p->d_name);
	}

	// Directory entry stream 을 처음으로 되돌림
	rewinddir(dp);
	while ((p = readdir(dp)) != NULL) {
		lstat(p->d_name, &stat);
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
