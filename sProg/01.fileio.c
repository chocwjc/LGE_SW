// 1byte만 읽어오는 프로그램 작성
#include <stdio.h>

int main(int argc, char *argv[])
{
	int size, read_bytes;
	char ch, buff[100];
	FILE *fp;

	if ((fp = fopen(argv[1], "r")) == NULL) {
		printf("Cannot open file for read\n");
		goto open_error;
	}

	while ((read_bytes = fgetc(fp)) != EOF)  {

		fputc(read_bytes, stdout);

		usleep(10000);
	}



read_error:
	fclose(fp);
open_error:

	return 0;
}
