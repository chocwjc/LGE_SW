#include <stdio.h>

int main(int argc, char **argv)
{
	int i, count, start, end, ch;
	FILE *fp1, *fp2;

	start = 1; 
	end = argc - 2;
	count = argc;

	if ((fp1 = fopen(argv[argc - 1], "w")) == NULL) {
		printf("Cannot open file for write\n");
		goto open_error;
	}

	for (i = start; i <= end; i++) {

		if ((fp2 = fopen(argv[i], "r")) == NULL) {
			printf("Cannot open file for read 2\n");
			goto open_error2;
		}
		while((ch = fgetc(fp2)) != EOF) {
			fputc(ch, fp1);
		}
		fclose(fp2);
	}

open_error2:
	fclose(fp1);
open_error:
	return 0;
}
