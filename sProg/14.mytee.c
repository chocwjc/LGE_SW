#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

const unsigned FLAG_APPEND =  O_APPEND | O_CREAT | O_WRONLY;
const unsigned FLAG_IGNORE =  O_TRUNC | O_CREAT | O_WRONLY;

int main(int argc, char **argv)
{
	char buff[1024];
	int i, fp, src_fp, opt, read_bytes, total_bytes, ptotal_bytes;
	int start_arg = 1;
	int flags = FLAG_IGNORE;

	while ((opt = getopt(argc, argv, "a")) != -1) {
		switch (opt) {
			case 'a':
				flags = FLAG_APPEND;
				start_arg++;
				break;
			default: /* '?' */
				break;
		}
	}

	src_fp = 0; // stdin
	for (i = start_arg; i < argc; i++) {

		int fpos;
		if((fp = open(argv[i], flags, 0666)) == -1) {
			printf("File open error\n");
			goto open_error;
		}
		fpos = lseek(fp, 0, SEEK_END);
		
		total_bytes = 0;
		while ((read_bytes = read(src_fp, buff, sizeof (buff))) > 0) {
			if (i == start_arg)
				write (1, buff, read_bytes);
			write (fp, buff, read_bytes);
		}

		close(src_fp);
		close(fp);
		if((fp = open(argv[i], O_RDONLY, 0666)) == -1) {
			printf("File open error\n");
			goto open_error2;
		}
		lseek(fp, fpos, SEEK_SET);
		src_fp = fp;
	}

open_error:
	close(src_fp);
open_error2:
	return 0;
}
