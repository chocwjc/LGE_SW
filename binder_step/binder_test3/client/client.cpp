
// client.cpp
#include "Android.h"

// 1. 드라이버의 정보를 보존하기 위해 클래스 도입
// 2. 둘 이상의 객체를 생성하는 것은 의미가 없으므로 싱글톤 패턴 도입
class ProcessState
{
	int mDriverFD;

	ProcessState() : mDriverFD(open_driver()) {}

	ProcessState(const ProcessState &p);
	ProcessState &operator=(const ProcessState &p);

	static ProcessState  *pInstance;
public:

	static ProcessState *self() // getinstance
	{
		if (pInstance == 0)
			pInstance = new ProcessState;
		return pInstance;
	}

	int get_driver() {return  open_driver(); }
	int open_driver() { return binder_open(128*1024); }
};
ProcessState *ProcessState::pInstance = 0;

// 3. 드라이버와 통신을 하기 위한 클래스를 도입
class IPCThreadState
{
	ProcessState *mProcess;
public:
	IPCThreadState(): mProcess(ProcessState::self()) {}

	// binder_call 에 대한 wrapper interface 
	int transact(int handle, int code, int *msg, int *reply)
	{
		int driver = mProcess->get_driver();
		return binder_call(driver, msg, reply, handle, code);
	}
};



int main(int argc, const char *argv[])
{
	ProcessState *proc(ProcessState::self());
	IPCThreadState *ipc(new IPCThreadState);

	int msg, reply;

	// binder call 을 사용하지 않고 통신 클래스의 래핑 인터페이스를 사용
	
	//int handle = binder_call(proc->get_driver(), (int*)"LedService", &reply,
	//		BINDER_SERVICE_MANAGER,	SVC_MGR_CHECK_SERVICE);

	int handle = ipc->transact(BINDER_SERVICE_MANAGER, SVC_MGR_CHECK_SERVICE,
			(int*)"LedService",  &reply);


	while (1)
	{
		//getchar(); binder_call(proc->get_driver(), &msg, &reply, handle, 1);
		getchar(); ipc->transact(handle, 1, &msg, &reply);
		//getchar(); binder_call(proc->get_driver(), &msg, &reply, handle, 2);
		getchar(); ipc->transact(handle, 2, &msg, &reply);
	}

	return 0;
}
