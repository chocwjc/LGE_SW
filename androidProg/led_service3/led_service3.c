/* Copyright 2008 The Android Open Source Project
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "binder.h"

int svcmgr_publish(struct binder_state *bs, uint32_t target, const char *name, void *ptr)
{
    int status;
    unsigned iodata[512/4];
    struct binder_io msg, reply;

    bio_init(&msg, iodata, sizeof(iodata), 4);
    bio_put_uint32(&msg, 0);  // strict mode header
    bio_put_string16_x(&msg, SVC_MGR_NAME);
    bio_put_string16_x(&msg, name);
    bio_put_obj(&msg, ptr);

    if (binder_call(bs, &msg, &reply, target, SVC_MGR_ADD_SERVICE))
        return -1;

    status = bio_get_uint32(&reply);

    binder_done(bs, &msg, &reply);

    return status;
}
/*
typedef int (*binder_handler)(struct binder_state *bs,
                              struct binder_transaction_data *txn,
                              struct binder_io *msg,
                              struct binder_io *reply);
*/

// RPC code 1 - LED on
// RPC code 2 - LED off
void led_on(void)  { printf("[led service] LED on\n"); }
void led_off(void) { printf("[led service] LED off\n"); }

typedef struct __token_t
{
	void (*on)(void);
	void (*off)(void);
} token_t;

int my_handler(struct binder_state *bs, struct binder_transaction_data *txn, struct binder_io *msg, struct binder_io *reply)
{ 

	token_t *led_service = (token_t*)txn->target.ptr;
	// check RPC code from binder
	switch (txn->code) {

		case 1:
			led_service->on();
			break;
		case 2:
			led_service->off();
			break;
	}
	return 0;

}

token_t token = {
	.on=led_on,
 	.off=led_off,
};
int main(int argc, char **argv)
{
    int fd;
    struct binder_state *bs;
    uint32_t svcmgr = BINDER_SERVICE_MANAGER;

    bs = binder_open(128*1024);
    if (!bs) {
        fprintf(stderr, "failed to open binder driver\n");
        return -1;
    }

		svcmgr_publish(bs, BINDER_SERVICE_MANAGER, "MyLedService", &token);

		binder_loop(bs, my_handler);

    return 0;
}
