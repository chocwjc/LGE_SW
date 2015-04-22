
// client.cpp
#include "Android.h"

// 1. 드라이버의 정보(binder FD)를 보존하기 위해 클래스 도입
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
IBinder *getService(const char *name)
{
	int reply;
	int sHandle = IPCThreadState::self()->transact(BINDER_SERVICE_MANAGER, SVC_MGR_CHECK_SERVICE, (int*)name, &reply);

	return new BpBinder(sHandle);
}

// 6. 단순 숫자에 불과한 RPC code 전송은 모호한 의미, 함수 호출의 인터페이스로 변경하기 위해 Class 도입
//      분산 시스템에서 서비스의 기능을 직접 제공하는 것이 아니라 서비스의 기능을 대신 요청하는 개념을 Proxy라고 함
//      Binder 의 서비스를 요청하는 wrapper 이므로 binder proxy - Bp 접두어를 붙임
class BpLedService
{
	IBinder *mRemote;
	int msg, reply;

public:
	LedService(IBinder *p) : mRemote(p) {}
	void ledOn()  {mRemote->transact(1, &msg, &reply);}
	void ledOff() {mRemote->transact(2, &msg, &reply);}
};


int main(int argc, const char *argv[])
{
	ProcessState *proc(ProcessState::self());

	int msg, reply;

	IBinder *binder = getService("Ledservice");
	BpLedService *ledService = new LedService(binder);
	
	while (1) {
		getchar(); ledService->ledOn();
		getchar(); ledService->ledOff();
	}

	return 0;
}
