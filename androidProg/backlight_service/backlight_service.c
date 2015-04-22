/* Copyright 2008 The Android Open Source Project
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
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

int backlight_get(void)
{
	int rtn  = -1;
	int fd, count;
	char buff[16];
	printf("[backlight service] get\n"); 

	fd = open("/sys/class/backlight/tegra-dsi-backlight.0/brightness", O_RDONLY);
	if (fd < 0) {
		printf("File open error\n");
		goto out;
	}

	count = read(fd, buff, sizeof (buff));
	if (count < 0) {
		printf("File read error\n");
		goto out_read;
	}
	buff[count] = 0;
	
	rtn = atoi(buff);
	printf("return value %d\n", rtn);

out_read:
	close(fd);
out:
	return rtn;
}
void backlight_set(int value) 
{ 
	int fd, count;
	char buff[16];

	printf("[backlight service] set\n");
	fd = open("/sys/class/backlight/tegra-dsi-backlight.0/brightness", O_RDWR);
	if (fd < 0) {
		printf("File open error\n");
		goto out;
	}

	printf("will write value %d\n", value);
	sprintf(buff, "%d", value);
	count = write(fd, buff, strlen(buff));
	if (count < 0) {
		printf("File write error\n");
		goto out_write;
	}
	printf("write value %s\n", buff);

out_write:
	close(fd);
out:
	return;
}

typedef struct __token_t
{
	int  (*get)(void);
	void (*set)(int);
} token_t;

int backlight_handler(struct binder_state *bs, struct binder_transaction_data *txn, struct binder_io *msg, struct binder_io *reply)
{ 
	//svcmgr_handler

	uint32_t value;
	token_t *backlight_service = (token_t*)txn->target.ptr;
	// check RPC code from binder
	switch (txn->code) {

		case 1: // get
			value = backlight_service->get();
			bio_put_uint32(reply, value);
			break;
		case 2: // set
			value = bio_get_uint32(msg);
			backlight_service->set(value);
			break;
	}
	return 0;
}

token_t token = {
	.get = backlight_get,
 	.set = backlight_set,
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

		svcmgr_publish(bs, BINDER_SERVICE_MANAGER, "com.lge.Backlight", &token);

		binder_loop(bs, backlight_handler);

    return 0;
}
