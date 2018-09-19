#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>

static int __init ofd_init(void)
{
	struct list_head *list;
	struct task_struct *task;
	bool flag = false;

	printk(KERN_INFO "rako: driver registered\n");
	printk(KERN_INFO "Current PID: %d\n",current->pid);
	printk(KERN_INFO "Current Prioriy: %d\n",current->normal_prio);
	printk(KERN_INFO "Parent's PID: %d\n",current->parent->pid);
	printk(KERN_INFO "Grand Parent's PID: %d\n",current->parent->parent->pid);
	list_for_each(list, &current->parent->children){
		task = list_entry(list, struct task_struct, sibling);
		printk(KERN_INFO " Brother's PID: %d\n",task->pid);
		if(task->pid == current->pid) flag=true;
	}
	if(flag) printk(KERN_INFO " Current in Brother: YES");
	else printk(KERN_INFO " Current in Brother: NO");
	return 0;
}
static void __exit ofd_exit(void)
{
	printk(KERN_INFO "rako: driver unregistered\n");
}
module_init(ofd_init);
module_exit(ofd_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Raspberry Korea");
MODULE_DESCRIPTION("Devive Driver Example");
