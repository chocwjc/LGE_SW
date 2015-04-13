#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

key_t key = 0x777;

struct msgbuf {
	long mtype;
	char mtext[100];
};

int main()
{
	int id;
	struct msgbuf msg;

	id = msgget(key, 0);
	if (id < 0) {
		id = msgget(key, IPC_CREAT | 0666);
	}
	
	msg.mtype = 1;
	strcpy(msg.mtext, "Hello\n");

	msgsnd(id, &msg, sizeof (msg) - sizeof (long), 0);
	sleep(1);

	memset(&msg, 0, sizeof (msg));
	msgrcv(id, &msg, sizeof (msg) - sizeof (long), 1, 0);

	printf("Message Type: %d\n", msg.mtype);
	printf("Message Data: %s\n", msg.mtext); 
	
	msgctl(id, IPC_RMID, 0);

	return 0;
}
