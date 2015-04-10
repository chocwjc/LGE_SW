#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("This is the original Program\n");
	
	char *exec_argv[] = 
		{"arg1", "arg2", "arg3", (char*)0};

	char *exec_nenv[] = 
		{"NAME=KIM", "NEXTNAME=XXX", "HOME=/XY", (char*)0};

	execve("./newpgm", exec_argv, exec_nenv);

	printf("This line should never get printed\n");
}
