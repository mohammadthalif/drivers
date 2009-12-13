#include <linux/module.h>
#include <linux/init.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");

struct timer_list timer;

void ex_timeout(unsigned long unused)
{
	printk(".");

	mod_timer(&timer, jiffies*HZ);
}

int __init ex_init(void)
{

	printk("initializing timer\n");
	init_timer(&timer);
	timer.function = ex_timeout;
	timer.expires = jiffies*HZ;
	add_timer(&timer);

	ex_timeout(0);

	return 0;

}

void __exit ex_exit(void)
{
	del_timer_sync(&timer);

	printk("timer dirver deregisterd\n");
}

module_init(ex_init);
module_exit(ex_exit);
