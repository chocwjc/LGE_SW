#include <linux/module.h> // module related
#include <linux/kernel.h> // printk
int init_module(void)
{
	printk("init_module\n");
	return 0;
}

void cleanup_module(void)
{
	printk("cleanup_module\n");
}
