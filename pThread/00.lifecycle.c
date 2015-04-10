#include <pthread.h>
#include <errno.h>


void *thread_routine(void *arg)
{
	return arg;
}

int main(int argc, char **argv)
{
	pthread_t thread_id;

	void *thread_result;
	int status;

	status = pthread_create(&thread_id, 0, thread_routine, 0);
	if (status != 0) 
		err_abort(status, "Create thread!\n");

	status = pthread_join(thread_id, &thread_result);

	if (status != 0)
		err_abort(status, "Join Thread\n");

	if (thread_result == NULL)
		return 0;
	else
		return 1;
}
