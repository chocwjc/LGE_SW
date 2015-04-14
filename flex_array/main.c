#include <stdio.h>
#include <linux/flex_array.h>

int main()
{
	struct flex_array *fa;

	int i;
	int numbers[] = {1,2,3,4,5,6,7,88,123,1,41,2,15,1,23,123};
	fa = flex_array_alloc(4, 40, 0);

	for (i=0; i < sizeof (numbers)/4; i++) 
		flex_array_put(fa, i, &numbers[i], 0);

	for (i=0; i < sizeof (numbers)/4; i++) 
		printf("%d\n",*(int*)flex_array_get(fa, i));

	
	flex_array_free(fa);

	return 0;
}
