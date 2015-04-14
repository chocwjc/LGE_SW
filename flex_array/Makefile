define+=-DPAGE_SIZE=4096
define+=-DCONFIG_X86_32
ALL: main

main: main.c flex_array.c
	gcc main.c flex_array.c -Iinclude $(define) -o a.out
