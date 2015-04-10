#include <stdio.h>
#include <pthread.h>

int global = 10;

void *foo(void *data)
{
	int i;

	for (i = 0; i < 5000000; i++) {
		global++;
	}

	pthread_exit(0);
}

int main()
{
	pthread_t tid1;
	pthread_t tid2;

	pthread_create(&tid1, 0, foo, 0);
	pthread_create(&tid2, 0, foo, 0);
	pthread_join(tid1, 0);
	pthread_join(tid2, 0);

	printf("%d\n", global);
}
	
