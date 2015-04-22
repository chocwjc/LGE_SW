/* Copyright 2008 The Android Open Source Project
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "binder.h"

uint32_t svcmgr_lookup(struct binder_state *bs, uint32_t target, const char *name)
{
    uint32_t handle;
    unsigned iodata[512/4];
    struct binder_io msg, reply;

    bio_init(&msg, iodata, sizeof(iodata), 4);
    bio_put_uint32(&msg, 0);  // strict mode header
    bio_put_string16_x(&msg, SVC_MGR_NAME);
    bio_put_string16_x(&msg, name);

    if (binder_call(bs, &msg, &reply, target, SVC_MGR_CHECK_SERVICE))
        return 0;

    handle = bio_get_ref(&reply);

    if (handle)
        binder_acquire(bs, handle);

    binder_done(bs, &msg, &reply);

    return handle;
}

unsigned token;
uint32_t handle, value;
struct binder_state *bs;
struct binder_io msg, reply;
unsigned iodata[512/4];

int set_backlight_brightness(int value)
{
	if (value < 0 || value > 255) {
		printf("[client] wrong input\n");
		return 0;
	}
	bio_put_uint32(&msg, value);
	printf("[client] send message  %d\n", value);
	binder_call(bs, &msg, &reply, handle, 2);
	return 1;
}
int get_backlight_brightness(void)
{
	binder_call(bs, &msg, &reply, handle, 1);
	value = bio_get_uint32(&reply);
	printf("[client] brightness:  %d\n", value);
	return value;
}

int main(int argc, char **argv)
{

		if (argc < 2) {
			printf("Usage: ./backlight_client {print|value}\n");
			return 0;
		}

    bs = binder_open(128*1024);
    if (!bs) {
        fprintf(stderr, "failed to open binder driver\n");
        return -1;
    }

		bio_init(&msg, iodata, sizeof (iodata), 4);

		handle = svcmgr_lookup(bs, BINDER_SERVICE_MANAGER, "com.lge.Backlight");
		printf("handle=%d\n", handle);

		if (!strcmp(argv[1], "print")) {
			get_backlight_brightness();
		} else {
			int i;
			for (i=0; i<strlen(argv[1]); i++) {
				if (!isdigit(argv[1][i])) {
					printf("[client] wrong input\n");
					return 0;
				}
			}
			value = atoi(argv[1]);
			set_backlight_brightness(value);
		}
    return 0;
}
