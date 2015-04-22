
// BnBacklightService.h

#ifndef __BNBACKLIGHTSERVICE_H__
#define __BNBACKLIGHTSERVICE_H__

#include <binder/Parcel.h>
#include "IBacklightService.h"
class BnBacklightService : public BnInterface<IBacklightService>
{
public:
	status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
	{
		int value = 0;
		switch(code)
		{
			case IBacklightService::BACKLIGHT_GET:
				value = get_backlight_brightness(); 
				reply->writeInt32(value);
				return NO_ERROR;
			case IBacklightService::BACKLIGHT_SET: 
				value = data.readInt32();
				set_backlight_brightness(value); 
				return NO_ERROR;
		}
		return BBinder::onTransact(code, data, reply, flags);
	}

	virtual int  get_backlight_brightness(void); 
	virtual void set_backlight_brightness(int); 
};

#endif
