
// client.cpp
#include "Android.h"


// 위의 코드는 안드로이드 프레임워크가 제공
// -----------------------------------------------------------------------------------------------------------------------
// 아래의 코드는 서비스 개발자가 제공해야 함


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
//ILedService *ILedService::asInterface(IBinder *p)
//{
//	return new BpLedService(p);
//}
IMPLEMENT_META_INTERFACE(LedService);

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
