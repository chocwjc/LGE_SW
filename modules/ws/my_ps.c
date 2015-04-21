#include <linux/module.h>
#include <linux/string.h>
#include <linux/time.h>
#include <linux/moduleparam.h>
#include <linux/mm.h>

static int  pid;
static char name[64];

int init_module(void)
{
	int i, res=0, len, find;
	struct mm_struct *mm;
	struct task_struct *p;
	char buffer[256];

	find = 0;

	for_each_process(p) {

		if (p->pid == pid || !strcmp(p->comm, name)) {
			find = 1;
			break;
		}
	}

	if (find == 0) {
		printk("no process\n");
		return 0;
	}

	mm = get_task_mm(p);
	if (!mm)
		goto out;
	if (!mm->arg_end)
		goto out_mm;	/* Shh! No looking before we're done */

 	len = mm->arg_end - mm->arg_start;
 
	if (len > PAGE_SIZE)
		len = PAGE_SIZE;
 
	res = access_process_vm(p, mm->arg_start, buffer, len, 0);

	// If the nul at the end of args has been overwritten, then
	// assume application is using setproctitle(3).
	if (res > 0 && buffer[res-1] != '\0' && len < PAGE_SIZE) {
		len = strnlen(buffer, res);
		if (len < res) {
		    res = len;
		} else {
			len = mm->env_end - mm->env_start;
			if (len > PAGE_SIZE - res)
				len = PAGE_SIZE - res;
			res += access_process_vm(p, mm->env_start, buffer+res, len, 0);
			res = strnlen(buffer, res);
		}
	}

	printk("%d %s\n", pid, buffer);
out:
out_mm:
	return 0;
}

void cleanup_module(void)
{
}

MODULE_LICENSE("GPL");
//module_init(init_module);
//module_exit(cleanup_module);

module_param(pid, int, 0);
module_param_string(name, name, sizeof (name), 0);
