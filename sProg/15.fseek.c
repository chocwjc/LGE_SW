#include <stdio.h>

int main()
{
	FILE *fp;

	fp = fopen("test", "a+");
	if (fp == NULL)
		printf("error\n");

	printf("%d\n", ftell(fp));

	fwrite("abcde\n",1,6,fp);

	printf("%d\n", ftell(fp));
	return 0;
}
