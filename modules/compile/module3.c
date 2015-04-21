#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

int init_module(void)
{
	struct  task_struct *p, *t;
	struct list_head *titer;
	for_each_process(p) {
		printk("pid=%d, comm=%s\n", p->pid, p->comm);

		for (titer = p->thread_group.next; titer != &p->thread_group; titer = titer->next){

			t = list_entry(titer, struct task_struct, thread_group);

			printk("\ttgid=%d, pid=%d, comm=%s\n", t->tgid, t->pid, t->comm);
		}
	}
	return 0;
}

void cleanup_module(void)
{
}

	
