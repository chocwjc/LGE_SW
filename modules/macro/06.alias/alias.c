#include <stdio.h>

void world_hello(void);
void hello_world(void) __attribute__((alias("world_hello")));

int main()
{
	hello_world();
	world_hello();
	return 0;
}

void world_hello(void)
{
	printf("Hello world\n");
}
