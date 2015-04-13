#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/* unsigned alarm(unsigned sec) 
	 1) Generate SIGALRM after second specified
	 2) The default handler for SIGALRM termiate process
	 3) RETURN VALUE: Remain sec of old alarm
	 4) If sec == 0, Alarm disabled (Only Return remain sec of old)
*/

void alm(int signo)
{
	printf("SIGALRM recieved\n");
}

int main()
{
	signal(SIGALRM, alm);
	alarm(10);

	printf("Process is pause\n");
	pause();
	printf("Process is wakeup\n");

	return 0;
}
