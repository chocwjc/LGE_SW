#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("This is the original Program\n");
	
	char *exec_argv[] = 
		{"arg1", "arg2", "arg3", (char*)0};

	execv("./newpgm", exec_argv);

	printf("This line should never get printed\n");

}
