
// IBacklightService.h

#ifndef __IBACKLIGHTSERVICE_H__
#define __IBACKLIGHTSERVICE_H__

#include <binder/IInterface.h>
using namespace android;

// 1. IInterface를 상속합니다.
class IBacklightService : public IInterface
{
public:
	// 2. 메타 코드 선언
	DECLARE_META_INTERFACE(BacklightService)

	enum { BACKLIGHT_GET = 1, BACKLIGHT_SET = 2 };

	virtual int  get_backlight_brightness(void) = 0;
	virtual void set_backlight_brightness(int)  = 0;
};

#endif
