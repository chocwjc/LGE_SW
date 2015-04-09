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

// 읽은 디렉토리로부터 모든 entry 의 이름 리턴
int main(int argc, char **argv)
{
	DIR *dp;
	struct dirent *p;

	dp = opendir(argv[1]);

	while ((p =  readdir(dp)) != NULL)  {
		printf("%s\n", p->d_name);
	}
	closedir(dp);
	return 0;
}
