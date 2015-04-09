#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char fname[20];
	int fisze;
} INFO;

int get_fsize(FILE *fp)
{
	int fsize, fpos;
	fpos = ftell(fp);
	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	fseek(fp, fpos,  SEEK_SET);
	return fsize;
}

int main(int argc, char **argv)
{
	FILE *fp1, *fp2;
	char buff[1024];
	INFO info;
	int start, end, i;
	int fsize, read_bytes;

	start = 1;
	end = argc - 2;

	if ((fp1 = fopen(argv[argc - 1], "w")) == NULL) {
		printf("Cannot open file for write\n");
		goto open_error;
	}

	for (i = start; i <= end; i++) {
		
		if((fp2 = fopen(argv[i], "r")) == NULL) {
			printf("Cannot open file for read\n");
			goto open_error2;
		}

		strcpy(info.fname, argv[i]);
		fsize = get_fsize(fp2);

		fwrite(&info, 1, sizeof (INFO), fp1);
		while ((read_bytes = fread(buff, 1, sizeof (buff), fp2)) != 0) {
			fwrite(buff, 1, read_bytes, fp1);
		}
		fclose(fp2);
	}

open_error2:
	fclose(fp1);
open_error:
	return 0;
}
