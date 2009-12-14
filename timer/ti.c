#include <linux/module.h>
#include <linux/init.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Example module on how to use timer function in linux");
MODULE_AUTHOR("Mohamed Thalib H <h.thalib@gmail.com>");

struct timer_list timer;

void ex_timeout(unsigned long unused)
{
	printk(KERN_ALERT ".");

	mod_timer(&timer, jiffies + msecs_to_jiffies(2*1000));
}

int __init ex_init(void)
{

#if 1
	printk("Initializing Timer 1 \n");
	init_timer(&timer);

	timer.function = ex_timeout;
	timer.expires = jiffies + msecs_to_jiffies(2*1000);

	add_timer(&timer);
#else
	printk("Initializing Timer 2 \n");
	setup_timer(&timer, ex_timeout, 123);
	mod_timer(&timer, jiffies + msecs_to_jiffies(5*2* 1000));

#endif

	return 0;

}

void __exit ex_exit(void)
{
	del_timer_sync(&timer);

	printk("Timer dirver deregisterd\n");
}

module_init(ex_init);
module_exit(ex_exit);
