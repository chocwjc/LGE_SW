#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	int i;

	for (i = 0; i < argc; i++) 
		printf("argv (%d): [%s]\n", i+1, argv[i]);
	
	for (i = 0; envp[i]; i++)
		printf("env (%d): [%s]\n", i+1, envp[i]);

	return 0;
}

