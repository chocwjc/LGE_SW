
// service_main.cpp
#include <binder/IServiceManager.h>
#include <binder/IBinder.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include "BnBacklightService.h"
using namespace android;

int main()
{
	defaultServiceManager()->addService(String16("com.lge.Backlight"), new BnBacklightService);
	IPCThreadState::self()->joinThreadPool();
}
