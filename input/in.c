#include <linux/module.h>
#include <linux/input.h>
#include <linux/init.h>

#define SW 0

MODULE_LICENSE("GPL");

struct input_dev *ex_dev;
unsigned int state;

void ex_timeout(unsigned long unused)
{
#if SW
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
#else
	if(state < 30) 
		input_report_rel(ex_dev, REL_X, 5);
	else if(state < 60)
		input_report_rel(ex_dev, REL_Y, 5);
	else if(state < 90)
		input_report_rel(ex_dev, REL_X, -5);
	else
		input_report_rel(ex_dev, REL_Y, -5);

	input_sync(ex_dev);

	if(((state++)>=120))
		state = 0;
		
#endif

	mod_timer(&ex_dev->timer, jiffies + msecs_to_jiffies(2*10));

}

int __init ex_init(void)
{
	printk("Example input device\n");

	ex_dev = input_allocate_device();

	ex_dev->name = "Example Input Device";
	ex_dev->phys = "A/Fake/Path";
	ex_dev->id.bustype = BUS_HOST;
	ex_dev->id.vendor = 0x0001;
	ex_dev->id.product = 0x0001;
	ex_dev->id.version = 0x0100;

#if KBD
	set_bit(EV_KEY, ex_dev->evbit);
	set_bit(KEY_B, ex_dev->keybit);
	set_bit(KEY_A, ex_dev->keybit);

#else
	set_bit(EV_REL, ex_dev->evbit);
	set_bit(REL_X, ex_dev->relbit);
	set_bit(REL_Y, ex_dev->relbit);

	set_bit(EV_KEY, ex_dev->evbit);
	set_bit(BTN_LEFT, ex_dev->keybit);
#endif
	
	if(!input_register_device(ex_dev)) {	
		printk("Example dirver registerd\n");
	}

	printk("initializing timer\n");

	init_timer(&ex_dev->timer);

	ex_dev->timer.function = ex_timeout;
	ex_dev->timer.expires = jiffies + msecs_to_jiffies(2*10);

	add_timer(&ex_dev->timer);

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
