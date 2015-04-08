#include <stdio.h>

int (*aaa(void))[2]
{
	static int a[2][2] = {{1,2},{3,4}};
	printf("hello\n");
	return a;
}

int (*(*bbb(void))(void))[2]
{
	return aaa;
}

int main()
{
	int (*(*(*p[2][2])(void))(void))[2] = {{bbb,bbb},{bbb,bbb}};
	int (*(*(*(*q)[2])(void))(void))[2] = p;

	printf("%d\n", q[0][0]()()[1][1]);

	return 0;
}

