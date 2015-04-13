#include "msglib.h"

int main()
{
	int qid,st, pid, parentpid;
	MSG_t msgrev, msgsnd;

	qid = OpenMQ(5000);
	parentpid = getpid();

	if(qid < 0)
	{
		printf("q open fail: %d\n",errno);	
		return -1;
	}
	pid = fork();
	if (pid == 0) {
		while(1) {
			sleep(1);
			while ((st = RecvMQ(qid, parentpid,&msgrev)) > 0)
				printf("recv : %s\n", msgrev.mtext);
		}
	} else {
		while(1) {
			memset(msgsnd.mtext,'\0',100); 
			printf("\ninput : ");
			gets(msgsnd.mtext);

			if(SendMQ(qid,1L,msgsnd)<=0)   {
				printf("q send fail: %d\n",errno);	
				break;
			}

			if(!strcmp(msgsnd.mtext, "exit"))    {
				printf("Client Process Exit\n");	
				break;
			}
			sleep(1);
		}
	}

	return 0;
	
}

