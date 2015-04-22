
// client.cpp
#include "Android.h"

// 1. 드라이버의 정보(FD)를 보존하기 위해 클래스 도입
//    둘 이상의 객체를 생성하는 것은 의미가 없으므로 싱글톤 패턴 도입
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

// 3. 드라이버와 통신(binder_call)을 하기 위한 클래스를 도입
//    둘 이상의 객체를 생성하는 것은 의미가 없으므로 싱글톤 패턴 도입
class IPCThreadState
{
	ProcessState *mProcess;
	
	IPCThreadState(): mProcess(ProcessState::self()) {}
	IPCThreadState(const IPCThreadState *i);
	IPCThreadState &operator=(const IPCThreadState *i);

	static IPCThreadState *iInstance;
public:

	static IPCThreadState *self()
	{
		if (iInstance == 0)
			iInstance = new IPCThreadState;
		return iInstance;
	}

	int transact(int handle, int code, int *msg, int *reply)
	{
		int driver = mProcess->get_driver();
		return binder_call(driver, msg, reply, handle, code);
	}
};
IPCThreadState  *IPCThreadState::iInstance = 0;

// 5. 핸들을 보관하는 모든 클래스를 하나의 타입으로 처리할수 있도록 부모 클래스를 도입
//    순수 가상 함수 (interface) 는 관례적으로 I Prefix
class IBinder {

public:
	virtual int transact(int code, int *msg, int *reply) = 0;
};


// 3. 핸들을(Service manager 로부터 받은 service 의 handle) 보관하기 위한 클래스 도입 
//		(new) 핸들을 관리하는 클래스는 Binder 를 상속
class BpBinder : public IBinder {

	int mHandle;

public:
	BpBinder(int handle) : mHandle(handle) {}

	int transact(int code, int *msg, int *reply)
	{
		return IPCThreadState::self()->transact(mHandle, code, msg, reply);
	}
};

// 4. 서비스의 handle 을 얻어오는 함수를 설계, 원래 IServiceManager 의 멤버 함수
//			실제 안드로이드 코드
//			sp<IServiceManager> sm = defaultServiceManager();
//			sm->getService(string16("LedService"));

//int *getService(const char *name)
//BpBinder *getService(const char *name)
IBinder *getService(const char *name)
{
	int reply;
	int sHandle = IPCThreadState::self()->transact(BINDER_SERVICE_MANAGER, SVC_MGR_CHECK_SERVICE, (int*)name, &reply);

	return new BpBinder(sHandle);
}


int main(int argc, const char *argv[])
{
	ProcessState *proc(ProcessState::self());

	int msg, reply;

	//int handle = IPCThreadState::self()->transact(BINDER_SERVICE_MANAGER, SVC_MGR_CHECK_SERVICE, (int*)"LedService",  &reply);
	IBinder *binder = getService("Ledservice");
	
	while (1)
	{
		getchar(); binder->transact(1, &msg, &reply);
		getchar(); binder->transact(2, &msg, &reply);
	}

	return 0;
}
