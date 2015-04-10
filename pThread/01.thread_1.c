#include <stdio.h>
#include <pthread.h>

int global = 10;

void *foo(void *data)
{
	int *val = (int*)data;
	++*val;

	pthread_exit(0);
}

int main()
{
	int local = 20;
	pthread_t tid;

	pthread_create(&tid, 0, foo, &local);
	pthread_join(tid, 0);

	pthread_cond_wait

	printf("%d\n", local);
}
	
