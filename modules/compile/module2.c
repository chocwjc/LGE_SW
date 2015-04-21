#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/mm.h>

int init_module(void)
{
	int i = 0;
	struct  task_struct *p;
	struct mm_struct *mm;
	for_each_process(p) {
		mm = p->mm;

		if (mm) {
			printk("start<%lp> end<%lp> pid=%d, comm=%s\n", 
					mm->arg_start, mm->arg_end, p->pid, p->comm);
			if (i++ > 15)
				break;
		}
	}
	return 0;
}

void cleanup_module(void)
{
}

	
