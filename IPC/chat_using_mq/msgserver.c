#include "msglib.h"

pid_t pidarr[20];
size_t pid_nums;

int chkpid(pid_t pid)
{
	int i;
	for (i = 0; i < pid_nums; i++) {
		if (pid == pidarr[i])
			return 1;
	}

	if (i == pid_nums) {
		printf("new pid arrive\n");
		pidarr[pid_nums++] =  pid;
	}
	return 0;
}

int main()
{
	int i, qid;
	MSG_t msg;

	long mtype;

	qid=CreateMQ(5000);

	if(qid<0)
	{
		printf("q open fail: %d\n",errno);	
		return -1;
	}
	while(1)
	{
		mtype = RecvMQ(qid, 1L, &msg);
		chkpid(mtype);

		if(mtype > 0)
		{
			if(!strcmp(msg.mtext, "exit"))
			{
				printf("Server Process Exit\n");	
				break;
			}
			printf("recv : %s\n",msg.mtext);	
		
			for (i = 1; i < pid_nums; i++) {	
				printf("Send to %d\n", pidarr[i]);
				if(SendMQ(qid, pidarr[i], msg)<0)
					break;
			}
		}
	}
	RemoveMQ(qid);

	return 0;
}

