#include <stdio.h>

int main(int argc, char **argv)
{
	int ch, count, open;
	FILE *fp1, *fp2;

	if ((fp1 = fopen(argv[1], "r")) == NULL) {
		printf("Cannot open file for read\n");
		goto open_error;
	}
	if ((fp2 = fopen(argv[2], "w")) == NULL) {
		printf("Cannot open file for write\n");
		goto open_error2;
	}
	
	while((ch = fgetc(fp1)) != EOF) {
		fputc(ch, fp2);
	}

	fclose(fp2);
open_error2:
	fclose(fp1);
open_error:
	return 0;
}
