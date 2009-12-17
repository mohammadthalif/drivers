#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>

MODULE_AUTHOR("MOHAMED THALIB H <hmthalib@gmail.com>");
MODULE_DESCRIPTION("Tasklet demo module");
MODULE_LICENSE("GPL");


void tas_fun(unsigned long t)
{
	printk("I AM INSIDE TASKLET\n");
}

DECLARE_TASKLET(tas, tas_fun, 0);


int __init tas_init(void)
{

	printk("Registerd taklet demo\n");

	tasklet_schedule(&tas);

	return 0;
}

void __exit tas_exit(void)
{

	printk("Unregisterd taklet demo\n");
	
}


module_init(tas_init);
module_exit(tas_exit);
