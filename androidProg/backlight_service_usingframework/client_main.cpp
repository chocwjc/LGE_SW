
// client_main.cpp

#include "BpBacklightService.h"
#include <ctype.h>

int main(int argc, char  **argv)
{
	int value;

	if (argc < 2) {
		printf("Usage: ./backlight_client {print|value}\n");
		return 0;
	}

	sp<ProcessState> proc(ProcessState::self());
	sp<IServiceManager> sm = defaultServiceManager();
	sp<IBinder> binder = sm->getService(String16("com.lge.Backlight"));
	sp<IBacklightService> backlightService = interface_cast<IBacklightService>(binder);

	if (!strcmp(argv[1], "print")) {
		value = backlightService->get_backlight_brightness();
		printf("[client] brightness:  %d\n", value);
	} else {
		int i;
		for (i=0; i<strlen(argv[1]); i++) {
			if (!isdigit(argv[1][i])) {
				printf("[client] wrong input\n");
				return 0;
			}
		}
		value = atoi(argv[1]);
		if (value < 0 || value > 255) {
			printf("[client] wrong input\n");
			return 0;
		}
		backlightService->set_backlight_brightness(value);
		printf("[client] send message  %d\n", value);
	}
	return 0;	
}
