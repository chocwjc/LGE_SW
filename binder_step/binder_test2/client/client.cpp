
// client.cpp
#include "Android.h"

// 1. 드라이버의 정보를 보존하기 위해 클래스 도입
// 2. 둘 이상의 객체를 생성하는 것은 의미가 없으므로 싱글톤 패턴 도입
class ProcessState
{
	int mDriverFD;

	// 유일한 객체를 반환하기 위해 정적 인터페이스를 도입
	ProcessState() : mDriverFD(open_driver()) {}

	// 복사와 대입 금지하기 위해 Private 생성자로 (정의가 아닌 선언)
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

	//ProcessState() : mDriverFD(open_driver()) {} // 객체의 임의 생성을 막기 위해 생성자를 Private 영역에 정의
	
	int get_driver() {return  open_driver(); }

	// Lowlevel interface for advenced programmer
	int open_driver() { return binder_open(128*1024); }
};


ProcessState *ProcessState::pInstance = 0;


int main(int argc, const char *argv[])
{
	//int fd = binder_open(128*1024);
	//ProcessState proc;
	//ProcessState *proc(new ProcessState); // == ProcessState *proc = new ProcessState;
	ProcessState *proc(ProcessState::self());

	int msg, reply;
	int handle = binder_call(proc->get_driver(), (int*)"LedService", &reply,
			BINDER_SERVICE_MANAGER,	SVC_MGR_CHECK_SERVICE);

	while (1)
	{
		getchar(); binder_call(proc->get_driver(), &msg, &reply, handle, 1);
		getchar(); binder_call(proc->get_driver(), &msg, &reply, handle, 2);
	}

	return 0;
}
