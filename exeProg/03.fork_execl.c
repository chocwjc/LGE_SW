#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	printf("This is the original Program\n");
	
	pid = fork();

	if (pid == 0)
		execl("./newpgm", "newpgm", "parm1", "parm2", "parm3",  (char*)0);

	wait(0);
	printf("This line should be printed after child\n");
	return 0;
}
