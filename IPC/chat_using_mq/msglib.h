#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct msg_q
{
	long to_mtype;

	long fm_mtype;
	char mtext[100];
} MSG_t;


int  CreateMQ(key_t);
int  OpenMQ(key_t);
long RecvMQ(int qid, long mtype, MSG_t *msgbuf);
long SendMQ(int qid, long mtype, MSG_t msgbuf );
int  RemoveMQ(int qid);


