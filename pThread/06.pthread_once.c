#include <stdio.h>
#include <pthread.h>

// tls - Thread Local Storage
pthread_key_t key;
void destructor(void *data)
{
	free(data);
}

// Once routine
pthread_once_t once_control = PTHREAD_ONCE_INIT;
void only_once_executed_routine(void)
{
	printf("Once Control!\n");
	pthread_key_create(&key, destructor);
}

void use_static_variable_routine(char *name)
{
	int *count;

	/* This routine execute only one thread - first thread calling it */
	pthread_once(&once_control, only_once_executed_routine);

	count = pthread_getspecific(key); // Find memory by key
	if (count == 0) {                 // if no memory found by key, Alloc memory and regist with key
		count = calloc(1, sizeof (int));
		pthread_setspecific(key, count);
		*count = 0;
	}
	++*count;
	printf("%s: %d\n", name, *count);
}

/* routine1 and routine2 access same local variable, but memory is separate  */
void *routine1(void *arg)
{
	use_static_variable_routine("1");
	use_static_variable_routine("1");
	use_static_variable_routine("1");
	use_static_variable_routine("1");
	use_static_variable_routine("1");

	pthread_exit(0);
}

void *routine2(void *arg)
{
	use_static_variable_routine("2");
	use_static_variable_routine("2");
	use_static_variable_routine("2");

	pthread_exit(0);
}

int main()
{
	pthread_t t1, t2;

	
	pthread_create(&t1, 0, routine1, 0);
	pthread_create(&t2, 0, routine2, 0);

	pthread_join(t1, 0);
	pthread_join(t2, 0);

	pthread_key_delete(key);

	return 0;
}
