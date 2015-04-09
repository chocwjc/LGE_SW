#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>

// Passwd 구조체의 내용
/*
struct passwd {
	char *pw_name;
	char *pw_passwd;
	int pw_uid;
	int pw_gid;
	char *pw_gecos;
	char *pw_dir;
	char *pw_shell;
};
*/

int main(int argc, char **argv)
{
	int i;
	struct stat stat;
	struct passwd *pwd;

	lstat(argv[1], &stat);
	
	// getpwuid() - uid 를 받고 passwd 구조체의 주소를 반환한다.
	pwd = getpwuid(stat.st_uid);
	printf("%-*s \n", 10, pwd->pw_name);

	return 0;
}


	
	
