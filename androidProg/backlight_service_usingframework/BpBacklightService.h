
// BpBacklightService.h

#ifndef __BPBACKLIGHTSERVICE_H__
#define __BPBACKLIGHTSERVICE_H__

#include <binder/IInterface.h>
#include <binder/IBinder.h>
#include <binder/Parcel.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
using namespace android;

#include "IBacklightService.h"
class BpBacklightService : public BpInterface<IBacklightService>	// 1. BpInterface 상속
{
	Parcel send, reply;	// msg, reply;
public:
	// 2. IBinder 포인터 부모에게 넘겨주기
	BpBacklightService(const sp<IBinder>& binder) : BpInterface<IBacklightService>(binder) {}
	virtual int  get_backlight_brightness(void);
	virtual void set_backlight_brightness(int value);
};

#endif
