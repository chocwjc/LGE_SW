// Word 를 count 프로그램 작성
#include <stdio.h>
int main(int argc, char **argv)
{
	int ch, count, open;
	FILE *fp;

	if ((fp = fopen(argv[1], "r")) == NULL) {
		printf("Cannot open file for read\n");
		goto open_error;
	}
	count = 0;
	open = 0;
	while ((ch = fgetc(fp)) != EOF) {

		if (isalnum(ch) && open == 0) {
			open = 1;
			count++;
		} else if (!isalnum(ch) && open == 1) {
			open = 0;
		}
	}

	printf("Counted word = %d\n", count);

	fclose(fp);
open_error:

	return 0;
}
