#include <stdio.h>
#include <sys/types.h>

int my_compare(void *a, void *b);
void generic_swap(void *a, void *b, ssize_t size);
void generic_bsort(void *arr, int len, ssize_t size, int (*compare)(const void*,const void*));


int main()
{
	int i, j;
	double array[10] = {
		5.5, 1.1, 3.3, 4.4, 6.6, 7.7, 8.8, 9.9, 10.10, 2.2
	};

	generic_bsort(array, 10, sizeof (double), my_compare);

	for (i = 0; i < 10; i++)
		printf("%lf\n", array[i]);

	return 0;
}

// 1 - a > b
// 0 - otherwise
int my_compare(void *a, void *b)
{
	double da, db;

	da = *(double*)a;
	db = *(double*)b;

	if (da > db)
		return 1;
	return  0;
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
void generic_bsort(void *arr, int len, ssize_t size, int (*compare)(const void*,const void*))
{
	int i, j;
	for (i = len-1; i >=0; i--) {
		for (j = 0; j < i; j++) {
			if (compare(arr + j*size, arr + (j+1)*size)) {
				generic_swap(arr + j*size, arr + (j+1)*size, size);
			}
		}
	}

}
