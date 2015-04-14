#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>

struct alarm_elem {
	int    seconds;
	time_t alarm_time;
	struct alarm_elem *link;
	char   message[64];
};

struct alarm_elem *alarm_list = NULL;
time_t current = 0;

pthread_mutex_t alarm_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  alarm_cond  = PTHREAD_COND_INITIALIZER;

void alarm_insert(struct alarm_elem *new);

void *alarm_thread(void *arg)
{
	struct timespec ts;
	printf("Alarm thread start\n");

	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec += 1000;

	while (1) {

		int status;
		struct alarm_elem *first;
		pthread_mutex_lock(&alarm_mutex);
		status = pthread_cond_timedwait(&alarm_cond, &alarm_mutex, &ts);
		printf("alarm_thread: unblocked");

		if (status == ETIMEDOUT) { // Timeout

			printf(" by timeout\n");
			/* Pop and Remove out-dated alarm element */
			struct alarm_elem **iter, *next;
			for (iter = &alarm_list; *iter;) {

				next = (*iter)->link;

				if ((*iter)->alarm_time > time(0))
					break;

				printf("Alarm: (%d) %s\n", (int)(*iter)->seconds, (*iter)->message);
				free(*iter);
				*iter = next;
				
			}
		} else {                   // Signaled
			printf(" by signal\n");
		}

		first = alarm_list;
		pthread_mutex_unlock(&alarm_mutex);

		printf("New alarm check.. \n");
		if (first == NULL) {
			clock_gettime(CLOCK_REALTIME, &ts);
			ts.tv_sec += 1000;
		} else {
			clock_gettime(CLOCK_REALTIME, &ts);
			printf("New alarm detect: \n");
			printf("  now %d, alarm %d\n", ts.tv_sec, first->alarm_time);
			ts.tv_sec = first->alarm_time;
		}

		printf("new alarm time %d\n", ts.tv_sec);
	}

	pthread_exit(0);
}

int main()
{
	pthread_t alarm_thread_pid;

	pthread_create(&alarm_thread_pid,  0, alarm_thread, NULL);

	while (1) {

		struct alarm_elem *new_alarm = 0;

		new_alarm = (struct alarm_elem*)calloc(1, sizeof (struct alarm_elem));
		
		printf("Alarm > ");
		scanf("%d %64[^\n]", (int*)&new_alarm->seconds, new_alarm->message);
		new_alarm->alarm_time = time(0) + new_alarm->seconds;

		printf("New alarm, apoch %u\n", (unsigned)new_alarm->alarm_time);

		pthread_mutex_lock(&alarm_mutex);
		alarm_insert(new_alarm);
		pthread_mutex_unlock(&alarm_mutex);
		pthread_cond_signal(&alarm_cond);
	}

	return 0;
}

void alarm_insert(struct alarm_elem *new)
{
	struct alarm_elem **next;
	next = &alarm_list;

	// insert by order increasing
	while (*next) {

		if (new->alarm_time < (*next)->alarm_time)
			break;

		next = &(*next)->link;
	}
	new->link = *next;
	*next = new;

	next = &alarm_list;
	while (*next) {
		printf("(%d) %s -> ", (int)(*next)->alarm_time, (*next)->message);
		
		next = &(*next)->link;
	}
	printf("end\n");
}
