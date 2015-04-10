#include <stdio.h>
#include <pthread.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int global = 0;


void *foo(void *data)
{
	pthread_mutex_lock(&mutex);
	sleep(3);
	global++;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
	return 0;
}

void *bar(void *data)
{
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&cond, &mutex);
	printf("Global = %d\n", global);
	pthread_mutex_unlock(&mutex);
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

