#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

/* Check Current process's signal mask */
void show_mask()
{
	sigset_t sigset;

	/*
		 int sigprocmask(int how, const sigset_t *set, sigset_t *oldset)

		 If set is NULL, then  the  signal  mask  is  unchanged  (i.e.,  how  is
		 ignored),  but  the  current  value  of the signal mask is nevertheless
		 returned in oldset (if it is not NULL).
 */
	if (sigprocmask(0, NULL, &sigset) < 0) 
		printf("sigprocmask() error\n");

	if (sigismember(&sigset, SIGINT)) printf("SIGINT is blocked\n");
	if (sigismember(&sigset, SIGQUIT)) printf("SIGQUIT is blocked\n");
	if (sigismember(&sigset, SIGUSR1)) printf("SIGUSR1 is blocked\n");
	if (sigismember(&sigset, SIGALRM)) printf("SIGALRM is blocked\n");

	printf("\n");
}

int main()
{
	sigset_t newmask, oldmask;

	// get empty (All-Zero) sigset
	sigemptyset(&newmask);
	
	// Masking SIGQUIT to block
	sigaddset(&newmask, SIGQUIT);

	// Set new signal block list 
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		printf("sigprocmask() error\n");

	// Check current block signal list
	show_mask();

	// Restore previous signal block list
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		printf("sigprocmask() error\n");

	exit(0);
}
