#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <getopt.h>
#include <string.h>
#include <grp.h>
#include <pwd.h>

#define MAX(x,y) 	((x) > (y) ? (x) : (y))

#define PRINT_ALL (0x01)
#define LONG_LIST (0x02)
#define RECURSIVE (0x04)
#define PRINT_INO (0x08)

#define IS_PRINT_ALL(x)			(((x) & PRINT_ALL) != 0)
#define IS_LONG_FORMAT(x)		(((x) & LONG_LIST) != 0)
#define IS_PRINT_SUBDIR(x)	(((x) & RECURSIVE) != 0)
#define IS_PRINT_INODE(x)		(((x) & PRINT_INO) != 0)

struct ls_result_format {
	size_t max_fil;
};


/* */
int parsing_option(int argc, char **argv, unsigned char *flag);

/*
	size 11 
 */
char *get_permstring(mode_t stmode) 
{
	int i;
	const char  rwx[] = "rwx";
	const char  xsS[] = "-xSs-xSs-xTt";
	static char permstring[11];

	strncpy(permstring, "----------", 10);
	
	// File type
	if (S_ISDIR(stmode))  permstring[0] = 'd';
	if (S_ISCHR(stmode))  permstring[0] = 'c';
	if (S_ISBLK(stmode))  permstring[0] = 'b';
	if (S_ISSOCK(stmode)) permstring[0] = 's';
	if (S_ISLNK(stmode))  permstring[0] = 'l';
	if (S_ISFIFO(stmode)) permstring[0] = 'p';

	// Permission string
	for (i = 0; i < 9; i++) 
		if (stmode >> (8-i) & 1UL)
			permstring[1+i] = rwx[i%3];

	for (i = 1; i <= 3; i++) {
		int special = (stmode & (1UL << (12-i))) != 0;
		int regular = (stmode & (1UL << (i-1)*3) != 0);
		permstring[i*3] = xsS[(i-1)*4 + special*2 + regular];
	}

	return permstring;
}

/*
	size 13 
 */
char *get_timestring(time_t stime)
{
	struct tm *tm;
	static char timestring[13];
	const char *monstring[12] = {"Jan", "Feb", "May", "Api", "Mar", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	tm = localtime(&stime);
	sprintf(timestring, "%3s %02d %02d:%02d",
			monstring[tm->tm_mon], tm->tm_mday, tm->tm_hour, tm->tm_min);

	return timestring;
}

/*
	 len is flexible
	 */
char *get_ownername(uid_t uid, size_t *len) 
{
	static char owner_name[16];	
	struct passwd *pwd;

	*len = 0;
	owner_name[0] = 0;

	pwd = getpwuid(uid);
	strcpy(owner_name, pwd->pw_name);
	*len = strlen(owner_name);

	return owner_name;
}

/*
	 len is flexible
	 */
char *get_groupname(gid_t gid, size_t *len) 
{
	static char group_name[16];	
	struct group *grp;

	*len = 0;
	group_name[0] = 0;

	grp = getgrgid(gid);
	strcpy(group_name, grp->gr_name);
	*len = strlen(group_name);

	return group_name;
}
/*
	 len is flexible
	 */
char *get_sizestring(mode_t stmode, dev_t rdev, size_t size, size_t *len) 
{
	static char size_string[16];
	*len = 0;
	size_string[0] = 0;

	if (S_ISCHR(stmode) || S_ISBLK(stmode)) 
		sprintf(size_string, "%3u, %3u", ((rdev>>8)&0xff), (rdev&0xff));
	else
		sprintf(size_string, "%u", size);

	*len = strlen(size_string);
	return size_string;
}

int traversal_dir(char *dir_name, unsigned char flag)
{
	DIR *dp;
	struct dirent *p;
	struct stat buf;
	
	int filesize;
	int filesize_len;
	int filename_len;
	int ownername_len;
	int groupname_len;
	
	int max_filename_len;
	int total_file_size;
	int max_ownername_len;
	int max_groupname_len;
	int max_filesize_len;

	char *ownername_str;
	char *groupname_str;
	char *sizestring_str;
	char *timestring_str;
	char *permstring_str;

	filesize = 0;
	max_filename_len  = 0;
	total_file_size   = 0;
	max_ownername_len = 0;
	max_groupname_len = 0;
	max_filesize_len  = 0;

	chdir(dir_name);

	dp = opendir(".");

	/* 1 pass, max file name length (long format)
		         max file size length (long format)
						 total file size (current dir)
						 max username length (long format)
						 max groupname length (long format)
  */
	if (IS_PRINT_SUBDIR(flag)) 
		printf("%s:\n", dir_name);

	while (p = readdir(dp)) {

		lstat(p->d_name, &buf);

		if (!IS_PRINT_ALL(flag) && p->d_name[0] == '.')
			continue;

		if (IS_LONG_FORMAT(flag)) {
			max_filename_len = MAX(max_filename_len, strlen(p->d_name));
			
			get_sizestring(buf.st_mode, buf.st_rdev, buf.st_size, &filesize_len);
			max_filesize_len = MAX(max_filesize_len, filesize_len);

			get_ownername(buf.st_uid, &ownername_len);
			max_ownername_len = MAX(max_ownername_len, ownername_len);

			get_groupname(buf.st_gid, &groupname_len);
			max_groupname_len = MAX(max_groupname_len, groupname_len);

			filesize +=  buf.st_size;
		}
	}

	rewinddir(dp);

	/* 2 pass, print for current directory files
	*/
	while (p = readdir(dp)) {

		int ret;
		char linkname[100];

		lstat(p->d_name, &buf);

		if (!IS_PRINT_ALL(flag))
		 if(p->d_name[0] == '.')
			continue;

		if (IS_PRINT_INODE(flag))
			printf("%d  ", buf.st_ino);

		if (IS_LONG_FORMAT(flag)){

			ownername_str =  get_ownername(buf.st_uid, &ownername_len);
			groupname_str =  get_groupname(buf.st_gid, &groupname_len);
			sizestring_str = get_sizestring(buf.st_mode, buf.st_rdev, buf.st_size, &filesize_len);
			timestring_str = get_timestring(buf.st_mtime);
			permstring_str = get_permstring(buf.st_mode);

			linkname[0] = 0;
			if (S_ISLNK(buf.st_mode)) {
				ret = readlink(p->d_name, linkname+3, sizeof (linkname-3));
				linkname[0] = '-';
				linkname[1] = '>';
				linkname[2] = ' ';
				linkname[ret+3] = 0;
			}

			printf("%10s %3d %-*s %-*s %*s %12s %s %s\n", 
					permstring_str, buf.st_nlink, 
					max_ownername_len, ownername_str,
					max_groupname_len, groupname_str,
					max_filesize_len, sizestring_str,
					timestring_str, p->d_name, linkname);

		} else {
			printf("%s ", p->d_name);
		}
	}
	printf("\n\n");

	/* 3 pass, goto subdir
	*/
	if (IS_PRINT_SUBDIR(flag)) {
		rewinddir(dp);

		while (p = readdir(dp)) {

			lstat(p->d_name, &buf);

			if (S_ISDIR(buf.st_mode)) {
				if (strcmp(p->d_name, ".") && strcmp(p->d_name, ".."))
					total_file_size += traversal_dir(p->d_name, flag);
			}
		}
	}

	closedir(dp);
	chdir("..");

	return total_file_size;
}

/* main function */
int main(int argc, char **argv)
{
	int arg_start, i, j;
	unsigned char flag = 0;
	char *start_dirname;

	arg_start = parsing_option(argc, argv, &flag);

	if (arg_start == argc) 
		start_dirname = ".";
	else
		start_dirname = argv[arg_start];

	traversal_dir(start_dirname, flag);

	return 0;
}
	
int parsing_option(int argc, char **argv, unsigned char *flag)
{
	int opt;
	int arg_start = 1;
	while ((opt = getopt(argc, argv, "alRi")) != -1) {
		switch (opt) {
		case 'a':
			*flag |= PRINT_ALL;
			break;
		case 'l':
			*flag |= LONG_LIST;
			break;
		case 'R':
			*flag |= RECURSIVE;
			break;
		case 'i':
			*flag |= PRINT_INO;
			break;
		default:
			break;
		}
	}
	return arg_start + optind - 1;
}
