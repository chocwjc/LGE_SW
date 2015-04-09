#include <stdio.h>
#include <dirent.h>
#include <errno.h>

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

// directory traversal 을 모듈화, chdir() 사용
void my_ls(char *dname)
{
	DIR *dp;
	struct dirent *p;

	chdir(dname);
	dp = opendir(".");

	while ((p =  readdir(dp)) != NULL)  {
		printf("%s\n", p->d_name);
	}
	closedir(dp);
}

int main(int argc, char **argv)
{
	my_ls(argv[1]);
	return 0;
}
