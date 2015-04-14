#include <stdio.h>
#include <pthread.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int global = 0;


void *foo(void *data)
{
	sleep(1);
	global++;
	pthread_cond_signal(&cond);
	return 0;
}

void *bar(void *data)
{
	printf("Bar start\n");
	pthread_mutex_lock(&mutex);
	printf("Bar Lock acquire\n");

	printf("Bar start wait for signal\n");
	pthread_cond_wait(&cond, &mutex);
	printf("Bar signaled\n");

	printf("Global = %d\n", global);
	pthread_mutex_unlock(&mutex);
	printf("Bar Lock release\n");
	return 0;
}

int main()
{
	pthread_mutex_init(&mutex, 0);
	pthread_cond_init(&cond, 0);
	pthread_t t1, t2;
	pthread_create(&t1, 0, foo, 0);
	pthread_create(&t2, 0, bar, 0);
	pthread_join(t1, 0);
	pthread_join(t2, 0);

	return 0;
}

