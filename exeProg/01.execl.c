#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("This is the original Program\n");
	
	execl("./newpgm", "newpgm", "parm1", "parm2", "parm3",  (char*)0);

	printf("This line should never get printed\n");

}
