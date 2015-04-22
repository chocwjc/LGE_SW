
// servier.cpp
#include "Android.h"

// 이상의 코드는 Android Framework 가 제공해야 함
// ------------------------------------------------------------------------------------------------------
// 이하의 코드는 Android Service 개발자가 구현해야 함

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


int main(int argc, const char *argv[])
{
	// 1. open binder
	ProcessState *proc(ProcessState::self());

	// 2. add service
	addService("LedService", new LedService);


	// 3. wait request
	//binder_loop(fd, my_handler); -> IPCThreadState::self()->joinThreadpool()
	IPCThreadState::self()->joinThreadPool();

	return 0;
}
