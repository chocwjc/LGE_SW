#include <stdio.h>
#include <unistd.h> // required 

#define LIST	(1)
#define INODE (2)
#define RECUR	(4)
#define ALL		(8)

int main(int argc, char **argv)
{
	int ch;
	int flag = 0;

	while ((ch = getopt(argc, argv, "liRa")) != -1) {

		switch (ch) {
			case 'l':
				flag |= LIST;
				break;
			case 'i':
				flag |= INODE;
				break;
			case 'R':
				flag |= RECUR;
				break;
			case 'a':
				flag |= ALL;
				break;
			default:
				break;
		}
	}
	if (flag & LIST)	 printf("l\n");
	if (flag & INODE)	 printf("i\n");
	if (flag & RECUR)	 printf("R\n");
	if (flag & ALL)		 printf("a\n");

	int i;

	printf("-------------\n");
	for (i = 0; i < argc; i++)
		printf("%s\n", argv[i]);

	return 0;
}

