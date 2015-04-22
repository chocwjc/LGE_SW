
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

// 1.  서비스의 기능이 구현된 클래스를 설계
//     1) BBinder 를 상속 받아야 한다.
//     2) onTransact 를 override 해야 한다
#if 0
int my_handler(int code, int msg, int* reply)
{
	switch (code)
	{
		case 1: printf("LED ON\n"); break;
		case 2: printf("LED OFF\n"); break;
	}
	return 0;
}
#endif
class LedService : public BBinder {

	//int my_handler(int code, int msg, int* reply)
	int onTransact(int code, int msg, int* reply)
	{
		switch (code)
		{
			case 1: printf("LED ON\n"); break;
			case 2: printf("LED OFF\n"); break;
		}
		return 0;
	}
};


int main(int argc, const char *argv[])
{
	// 1. open binder
	int fd = binder_open(128*1024);

	// 2. add service
	int reply;
	binder_call(fd, (int*)"LedService", &reply,
			BINDER_SERVICE_MANAGER, SVC_MGR_ADD_SERVICE);

	// 3. wait request
	binder_loop(fd, my_handler);
	return 0;
}
