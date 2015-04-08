#include <stdio.h>
#include <sys/types.h>


int main()
{
	double a, b;

	a = 1.111;
	b = 2.222;

	generic_swap(&a, &b, sizeof (double));

	printf("%lf\n", a);
	printf("%lf\n", b);


	return 0;
}

void generic_swap(void *a, void *b, ssize_t size)
{

	int i;
	char *pa, *pb, t;

	pa = (char*)a;
	pb = (char*)b;

	for (i=0; i<sizeof(double); i++,pa++,pb++) {
		t = *pa;
		*pa = *pb;
		*pb = t;
	}

}
