#include <stdio.h>
#include <string.h>

char *cut(char *buf, char *dest, int pos)
{
	char *ptr;

	do {
		while (*buf == ' ' && *buf) buf++;
		ptr = buf;
		while (*buf != ' ' && *buf) buf++;
	
	} while (--pos > 0);

	strncpy(dest, ptr, buf - ptr);
	dest[buf-ptr+1] = 0;

	return buf;
}

int main()
{
	char *str = " 123  456 789              000";
	char buf[30];

	cut(str, buf, 1);
	printf("%s\n", buf);

	cut(str, buf, 2);
	printf("%s\n", buf);

	cut(str, buf, 3);
	printf("%s\n", buf);

	cut(str, buf, 4);
	printf("%s\n", buf);

	printf("%s\n", buf);
	return 0;
}
