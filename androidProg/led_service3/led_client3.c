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

int main(int argc, char **argv)
{
    uint32_t handle;
    struct binder_state *bs;
		struct binder_io msg, reply;
		unsigned iodata[512/4];

    bs = binder_open(128*1024);
    if (!bs) {
        fprintf(stderr, "failed to open binder driver\n");
        return -1;
    }

		// @msg iodata, 
		bio_init(&msg, iodata, sizeof (iodata), 4);

		handle = svcmgr_lookup(bs, BINDER_SERVICE_MANAGER, "MyLedService");
		printf("handle=%d\n", handle);

		while (1) {
			getchar(); binder_call(bs, &msg, &reply, handle, 1); // LED on
			getchar(); binder_call(bs, &msg, &reply, handle, 2); // LED off;
		}

    return 0;
}
