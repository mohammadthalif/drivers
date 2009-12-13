#include <linux/module.h>
#include <linux/input.h>
#include <linux/init.h>


MODULE_LICENSE("GPL");

struct input_dev *ex_dev;

void ex_timeout(unsigned long unused)
{
	int i;

	for(i=0; i<=4; i++){
		input_report_key(ex_dev, KEY_A, 1);
		input_sync(ex_dev);
		input_report_key(ex_dev, KEY_A, 0);
	       	input_sync(ex_dev);
	}

	for(i=0; i<=4; i++){
		input_report_key(ex_dev, KEY_B, 1);
		input_sync(ex_dev);
		input_report_key(ex_dev, KEY_B, 0);
		input_sync(ex_dev);
	}

	printk(".");

	mod_timer(&ex_dev->timer, jiffies*4*HZ);

}

int __init ex_init(void)
{
	printk("Example input device\n");

	ex_dev = input_allocate_device();

	ex_dev->name = "Example Input Device";
	ex_dev->id.bustype = BUS_HOST;
	ex_dev->id.vendor = 0x0001;
	ex_dev->id.product = 0x0001;
	ex_dev->id.version = 0x0100;

	set_bit(EV_KEY, ex_dev->evbit);
	set_bit(KEY_B, ex_dev->keybit);
	set_bit(KEY_A, ex_dev->keybit);
	
	if(!input_register_device(ex_dev)) {	
		printk("Example dirver registerd\n");
	}

	printk("initializing timer\n");
	init_timer(&ex_dev->timer);
	ex_dev->timer.function = ex_timeout;
	ex_dev->timer.expires = jiffies*HZ;
	add_timer(&ex_dev->timer);

	ex_timeout(0);

	return 0;

}

void __exit ex_exit(void)
{
	del_timer_sync(&ex_dev->timer);
	input_unregister_device(ex_dev);
	printk("Example dirver deregisterd\n");
}

module_init(ex_init);
module_exit(ex_exit);
