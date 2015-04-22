
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
	virtual ~IBinder() {}
};


// 3. 핸들을(Service manager 로부터 받은 service 의 handle) 보관하기 위한 클래스 도입 
//		(new) 핸들을 관리하는 클래스는 Binder 를 상속
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
//			실제 안드로이드 코드
//			sp<IServiceManager> sm = defaultServiceManager();
//			sm->getService(string16("LedService"));
IBinder *getService(const char *name)
{
	int reply;
	int sHandle = IPCThreadState::self()->transact(BINDER_SERVICE_MANAGER, SVC_MGR_CHECK_SERVICE, (int*)name, &reply);

	return new BpBinder(sHandle);
}

// 8. Proxy 구현을 쉽게 할수 있도록 클래스를 설계
//      모든 binder Proxy 는 Binder fd 를 가지고 있어야 하기 때문에 공통 부분을 부모로 분리
class BpRefBase {
	IBinder *mRemote;
public:
	BpRefBase(IBinder *p) : mRemote(p) {};
	IBinder *remote() { return mRemote; }
};

// 위의 코드는 안드로이드 프레임워크가 제공
// -----------------------------------------------------------------------------------------------------------------------
//

// 7. 서비스 Proxy 와 서비서 Stub 이 ledOn() 과 ledOff()를 구현하도록 강제하기 위하여 Interface 를 도입
class ILedService {
	
public:
	virtual void ledOn()  = 0;
	virtual void ledOff() = 0;
	virtual ~ILedService() {}

	// ? ILedService 가 어떻게 BpLedService 를 미리 알수 있는가?
	//static ILedService *asIterface(IBinder *p) {return new BpLedService(p);}

	// ILedService 가 미리 asInterface 를 실제 구현하는 대신, 선언부만 남겨놓고 Proxy개발자가 직접 구현하도록 한다.
	static ILedService *asInterface(IBinder *p);
};


// 9. 다중 상속을 단일 상속으로 변경할수 있도록 하기 위해 새로운 클래스 도입
//    Android Framework 는 사용자가 어떤 Service 를 추가할지를 모르기 때문에 IInterface 를 구현할때마다 그것을 상속받는 BpInterface 를 설계해야 함
//    이 문제를 해결하기 위해 Template 를 사용하여 CRTP를 구현
// template class BpInterface : public ILedService, public BpRefBase
template <typename INTERFACE> class BpInterface : public INTERFACE, public BpRefBase
{
public:
	BpInterface(IBinder *p) : BpRefBase(p){}
};

// 6. 단순 숫자에 불과한 RPC code 전송은 모호한 의미, 함수 호출의 인터페이스로 변경하기 위해 Class 도입
//      분산 시스템에서 서비스의 기능을 직접 제공하는 것이 아니라 서비스의 기능을 대신 요청하는 개념을 Proxy라고 함
//      Binder 의 서비스를 요청하는 wrapper 이므로 binder proxy - Bp 접두어를 붙임
//    이제 Binder Proxy service 를 구현할 경우 BpRefBase 를 상속
// class BpLedService : public ILedService, public BpRefBase

// 이제 Proxy 를 설계하는 사람은 BpInterface 만 상속
class BpLedService  : public BpInterface<ILedService>
{
	//IBinder *mRemote;
	int msg, reply;

public:
	~BpLedService() {}
	BpLedService(IBinder *p) : BpInterface(p) {} // 부모의 private 멤버를 초기화하기 위해
	void ledOn()  {remote()->transact(1, &msg, &reply);}
	void ledOff() {remote()->transact(2, &msg, &reply);}
};

// 이제 Proxy 를 설계하는 사람은 ILedService 의 asInterface 실제 구현부를 작성해야 함
ILedService *ILedService::asInterface(IBinder *p)
{
	return new BpLedService(p);
}

int main(int argc, const char *argv[])
{
	ProcessState *proc(ProcessState::self());

	int msg, reply;

	IBinder *binder = getService("Ledservice");
	//BpLedService *ledService = new BpLedService(binder);
	//ILedService *ledService = (ILedService*)new BpLedService(binder); // 명확한 변환 연산자 사용하도록 변경
	//ILedService *ledService = new ILedService::asInterface(new BpLedService(binder)); // 사용자가 BpLedService 를 알 필요가 없도록 한다.
	ILedService *ledService = ILedService::asInterface(binder);
	
	while (1) {
		getchar(); ledService->ledOn();
		getchar(); ledService->ledOff();
	}

	return 0;
}
