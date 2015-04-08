#include <stdio.h>

unsigned noif_fold_count1(unsigned num)
{
	unsigned t1, t2, t;

	t1 = num      & 0x55555555;
	t2 = (num>>1) & 0x55555555;
	t  = t1 + t2;

	t1 = t        & 0x33333333;
	t2 = (t>>2)   & 0x33333333;
	t  = t1 + t2;

	t1 = t        & 0x0f0f0f0f;
	t2 = (t>>4)   & 0x0f0f0f0f;
	t  = t1 + t2;

	t1 = t        & 0x00ff00ff;
	t2 = (t>>8)   & 0x00ff00ff;
  t  = t1 + t2;

	t1 = t        & 0x0000ffff;
	t2 = (t>>16)  & 0x0000ffff;
	t  = t1 + t2;

	return t;
	
}

unsigned noif_fold_most1(unsigned num)
{
	unsigned t1, t2, t3, t4, t;

	t1 = num      & 0xaaaaaaaa;
	t2 = num      & 0x55555555;
	t  = t1  :

	return t;
	
}

int main()
{

	unsigned int num = 0x1fffffff;

	printf("%p\n", noif_fold_most1(num));

	return 0;
}
