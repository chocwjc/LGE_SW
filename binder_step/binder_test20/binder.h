
#ifndef __BINDER_H__
#define __BINDER_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BINDER_SERVICE_MANAGER 0

#define SVC_MGR_ADD_SERVICE 	0xFFFFFFF0
#define SVC_MGR_CHECK_SERVICE   0xFFFFFFF1

#define BINDER_PATH		"/tmp/binder"

bool server_init = false;
bool client_init = false;


int binder_open(int mapsize)
{
	return rand() % 100;
}

int create_pipe(const char* path, int mode)
{
	int ret = mkfifo(path, 0600);
	if (ret < 0 && errno != EEXIST)
	{
		perror("mkfifo");
		exit(-1);
	}

	int fd = open(path, mode);
	if(fd < 0)
	{
		perror("open");
		exit(-1);
	}

	return fd;
}

int binder_fd = 0;
const char* service_name;
int binder_call(int binder, int* msg, int* reply, int target, int code)
{
	if (code == SVC_MGR_ADD_SERVICE)
	{
		if (server_init == false)
		{
			service_name = reinterpret_cast<const char*>(msg);
			server_init = true;
			binder_fd = create_pipe(BINDER_PATH, O_RDWR);
		}
		return 0;
	}
	else if (code == SVC_MGR_CHECK_SERVICE)
	{
		if (client_init == false)
		{
			client_init = true;
			binder_fd = create_pipe(BINDER_PATH, O_WRONLY);
		}
		return -1;
	}

	if (client_init == false)
		return -1;

	int rpc_code = code;
	return write(binder_fd, &rpc_code, sizeof(int));
}

typedef int(*binder_handler)(int code, int msg, int* reply);
void binder_loop(int binder, binder_handler func)
{
	printf("[%s] running...\n", service_name);
	int msg, reply;
	int readn, rpc_code;
	while (true)
	{
		readn = read(binder_fd, &rpc_code, sizeof(int));
		func(rpc_code, msg, &reply);
	}
}

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

// 5. 핸들을 보관하는 모든 클래스를 하나의 타입으로 처리할수 있도록 부모 클래스를 도입
class IBinder {

public:
	virtual int transact(int code, int *msg, int *reply) = 0;
	virtual ~IBinder() {}
};

// 2.  안드로이드 프레임워크는 서비스 개발을 쉽게 하기 위하여 BBinder 제공
//     IBinder 는 service측에서 BBinder, client 측에서 BpBinder 로 상속됨
//     IBinder 는 순수 가상 함수로 transact() 를 가지고 있으며 이를 구현해야 함
class BBinder : public IBinder {

public:
	int transact(int code, int *msg, int *reply)
	{
		return onTransact(code, msg, reply);
	}

	// Interface 가 아닌 경우 정책을 강요해서는 안된다.
	// 따라서 순수 가상 함수가 아닌 그냥 가상 함수로
	virtual int onTransact(int, int*, int*) {return 0;} 
};

// 4. 다중 상속을 단일 상속으로 변경하기 위하여 아래의 클래스 도입
//     Android Framework 가 제공
//     역시 template 를 사용한  CCRP 도입
template<typename INTERFACE>
class BnInterface : public BBinder, public INTERFACE
{
public:
	IBinder *onAsBinder() { return this;}
};


IBinder *server;

void addService(const char *name, IBinder *p)
{
	int reply;
	int fd = ProcessState::self()->get_driver();
	server = p;
	binder_call(fd, (int*)name, &reply, BINDER_SERVICE_MANAGER, SVC_MGR_ADD_SERVICE);
}

// 3. 드라이버와 통신(binder_call)을 하기 위한 클래스를 도입
// JoinThreadPool() 구현
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

	// binder_loop 의 wrapper
	void joinThreadPool()
	{
		int driver = mProcess->get_driver();

		//Class 의 일반 member method 를 function pointer 로 넘기기 위해서는 this를 지정하는 특별한 문법이 필요하므로
		//this 가 필요없는 static member method 로 우회하도록 함
		//binder_loop(driver, server->transact());		
		binder_loop(driver, my_handler);
	}

	static int my_handler(int code, int msg, int *reply)
	{
		server->transact(code, &msg, reply);
	}
};
IPCThreadState  *IPCThreadState::iInstance = 0;


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

// 12. 인터페이스 설계를 쉽게 할수 있도록 새로운 클래스 도입
class IInterface {
public:
	//static ILedService *asInterface(IBinder *p);
	IBinder *asBinder() { return this ? onAsBinder() : 0; }
	virtual IBinder *onAsBinder() = 0;
};

#define DECLARE_META_INTERFACE(INTERFACE) \
	static I##INTERFACE *asInterface(IBinder *p)

#define IMPLEMENT_META_INTERFACE(INTERFACE) \
	I##INTERFACE *I##INTERFACE::asInterface(IBinder *p) { return new Bp##INTERFACE(p); }


// 7.  서비스 Proxy 와 서비서 Stub 이 ledOn() 과 ledOff()를 구현하도록 강제하기 위하여 Interface 를 도입
// 11. asBinder 라는 타입변환 연산자 추가
//       Service Interface -> Binder interface
//       실제 구현은 Service interface 와 Binder interface 를 상속받는 BpLedService 에서 이루어짐
//     Null check를 우회하도록 한다.
// 이제 Interface 를 구현하는 사람은 IInterface 를 상속하고 META_INTERFACE 사용
class ILedService : public IInterface {
	
public:
	virtual void ledOn()  = 0;
	virtual void ledOff() = 0;
	virtual ~ILedService() {}

	// Declear
	DECLARE_META_INTERFACE(LedService);
	//static ILedService *asInterface(IBinder *p);
};


// 9. 다중 상속을 단일 상속으로 변경할수 있도록 하기 위해 새로운 클래스 도입
template <typename INTERFACE> class BpInterface : public INTERFACE, public BpRefBase
{
public:
	BpInterface(IBinder *p) : BpRefBase(p){}
	IBinder *onAsBinder() {return remote();}
};
#endif
