obj-m = my_ps.o

default:
	make -C /usr/src/tegra SUBDIRS=$(PWD) modules

.PHONY: clean
clean:
	rm *.o *.
