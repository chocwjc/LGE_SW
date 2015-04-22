
// servier.cpp
#include "Android.h"

// 2.  안드로이드 프레임워크는 서비스 개발을 쉽게 하기 위하여 BBinder 제공
//     IBinder 는 service측에서 BBinder, client 측에서 BpBinder 로 상속됨
//     IBinder 는 순수 가상 함수로 transact() 를 가지고 있으며 이를 구현해야 함
class BBinder : public : IBinder {

public:
	int transact(int code, int *msg, int *reply)
	{
		return onTransact(code, msg, reply);
	}

	// Interface 가 아닌 경우 정책을 강요해서는 안된다.
	// 따라서 순수 가상 함수가 아닌 그냥 가상 함수로
	virtual int onTransact(int, int*, int*) {return 0;} 
}

// 4. 다중 상속을 단일 상속으로 변경하기 위하여 아래의 클래스 도입
//     Android Framework 가 제공
//     역시 template 를 사용한  CCRP 도입
template<typename INTERFACE>
class BnInterface : public BBinder, public INTERFACE
{
}

// 1.  서비스의 기능이 구현된 클래스를 설계
//     1) BBinder 를 상속 받아야 한다. ->  BnInterface
//     2) onTransact 를 override 해야 한다
// 3.  Client 와 동일한 interface 를 사용하기 위해 ILedService 상속 -> Bninterface
//class LedService : public BBinder, public Interface
class LedService : public BnInterface <ILedService> 
{
public:

	int onTransact(int code, int msg, int* reply)
	{
		switch (code)
		{
			case 1: ledOn(); break;
			case 2: ledOff(); break;
		}
		return 0;
	}

	void ledOn()  { printf("LED ON\n");}
	void ledOff() { printf("LED OFF\n");}
};

IBinder *server;

void addService(const char *name, IBinder *p)
{
	int reply;
	server = p;
	binder_call(fd, (int*)name, &reply, BINDER_SERVICE_MANAGER, SVC_MGR_ADD_SERVICE);
}


int main(int argc, const char *argv[])
{
	// 1. open binder
	//int fd = binder_open(128*1024);
	ProcessState *proc(ProcessState::self());

	// 2. add service
	//binder_call(fd, (int*)"LedService", &reply, BINDER_SERVICE_MANAGER, SVC_MGR_ADD_SERVICE);
	//sp<IServiceManager> sm =  defaultServiceManager(); ==  IServiceManager::self()
	//sm->addService(String16("LedService"), new LedService)
	addService("LedService", new LedService);


	// 3. wait request
	binder_loop(fd, my_handler);
	return 0;
}
