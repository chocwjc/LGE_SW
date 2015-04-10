#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("This is the original Program\n");
	
	char *nenv[] = 
		{"NAME=KIM", "NEXTNAME=XXX", "HOME=/XY", (char*)0};

	execle("./newpgm",
		 	"newpgm", "parm1", "parm2", "parm3",  (char*)0,
			nenv);

	printf("This line should never get printed\n");

}
