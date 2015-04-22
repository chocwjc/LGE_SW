
// BpBacklightService.cpp
#include "BpBacklightService.h"

int  BpBacklightService::get_backlight_brightness()
{
	int value;
	remote()->transact(IBacklightService::BACKLIGHT_GET, send, &reply);
	value = reply.readInt32();
	return value;
}

void BpBacklightService::set_backlight_brightness(int value)
{ 
	send.writeInt32(value);
	remote()->transact(IBacklightService::BACKLIGHT_SET, send, &reply);
}

