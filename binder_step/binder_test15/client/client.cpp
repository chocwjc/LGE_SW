
// client.cpp
#include "Android.h"

// 1. 드라이버의 정보(binder FD)를 보존하기 위해 클래스 도입
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
class IBinder {

public:
	virtual int transact(int code, int *msg, int *reply) = 0;
	virtual ~IBinder() {}
};


// 3. 핸들을(Service manager 로부터 받은 service 의 handle) 보관하기 위한 클래스 도입 
class BpBinder : public IBinder {

	int mHandle;

public:
	~BpBinder() {}
	BpBinder(int handle) : mHandle(handle) {}

	int transact(int code, int *msg, int *reply)
	{
		return IPCThreadState::self()->transact(mHandle, code, msg, reply);
	}
};

// 4. 서비스의 handle 을 얻어오는 함수를 설계, 원래 IServiceManager 의 멤버 함수
IBinder *getService(const char *name)
{
	int reply;
	int sHandle = IPCThreadState::self()->transact(BINDER_SERVICE_MANAGER, SVC_MGR_CHECK_SERVICE, (int*)name, &reply);

	return new BpBinder(sHandle);
}

// 8. Proxy 구현을 쉽게 할수 있도록 클래스를 설계
class BpRefBase {
	IBinder *mRemote;
public:
	BpRefBase(IBinder *p) : mRemote(p) {};
	IBinder *remote() { return mRemote; }
};

// 10. 
template<typename INTERFACE> INTERFACE *interface_cast(IBinder *p)
{
	return INTERFACE::asInterface(p);
}


// 위의 코드는 안드로이드 프레임워크가 제공
// -----------------------------------------------------------------------------------------------------------------------
// 아래의 코드는 서비스 개발자가 제공해야 함

// 12. 인터페이스 설계를 쉽게 할수 있도록 새로운 클래스 도입
#if 0
class IInterface {
public:
	static ILedService *asInterface(IBinder *p);
	IBinder *asBinder() { return this ? onAsBinder() : 0; }
	IBinder *onAsBinder() = 0;
};
#endif

// 7.  서비스 Proxy 와 서비서 Stub 이 ledOn() 과 ledOff()를 구현하도록 강제하기 위하여 Interface 를 도입
// 11. asBinder 라는 타입변환 연산자 추가
//       Service Interface -> Binder interface
//       실제 구현은 Service interface 와 Binder interface 를 상속받는 BpLedService 에서 이루어짐
//     Null check를 우회하도록 한다.
class ILedService {
	
public:
	virtual void ledOn()  = 0;
	virtual void ledOff() = 0;
	virtual ~ILedService() {}

	static ILedService *asInterface(IBinder *p);
	IBinder *asBinder() { return this ? onAsBinder() : NULL; }
	virtual IBinder *onAsBinder() = 0;
};


// 9. 다중 상속을 단일 상속으로 변경할수 있도록 하기 위해 새로운 클래스 도입
template <typename INTERFACE> class BpInterface : public INTERFACE, public BpRefBase
{
public:
	BpInterface(IBinder *p) : BpRefBase(p){}
};

// 6. 단순 숫자에 불과한 RPC code 전송은 모호한 의미, 함수 호출의 인터페이스로 변경하기 위해 Class 도입
class BpLedService  : public BpInterface<ILedService>
{
	int msg, reply;

public:
	~BpLedService() {}
	BpLedService(IBinder *p) : BpInterface(p) {} // 부모의 private 멤버를 초기화하기 위해
	void ledOn()  {remote()->transact(1, &msg, &reply);}
	void ledOff() {remote()->transact(2, &msg, &reply);}

	//
	//IBinder *asBinder(ILedService *p) { return remote(); }
	IBinder *onAsBinder() { return remote(); }
};

// 이제 Proxy 를 설계하는 사람은 ILedService 의 asInterface 실제 구현부를 작성해야 함
ILedService *ILedService::asInterface(IBinder *p)
{
	return new BpLedService(p);
}

int main(int argc, const char *argv[])
{
	ProcessState *proc(ProcessState::self());
	IBinder *binder = getService("Ledservice");
	ILedService *ledService = interface_cast<ILedService>(binder);

	int msg, reply;

	
	while (1) {
		getchar(); ledService->ledOn();
		getchar(); ledService->ledOff();
	}

	return 0;
}
