// BnBacklightService.cpp
#include "BnBacklightService.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int  BnBacklightService::get_backlight_brightness(void)
{ 
	int rtn  = -1;
	int fd, count;
	char buff[16];
	
	printf("[BacklightService] get\n"); 

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

void BnBacklightService::set_backlight_brightness(int value)
{
	int fd, count;
	char buff[16];

	printf("[BacklightService] set\n"); 

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

