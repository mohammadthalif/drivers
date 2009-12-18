#include <linux/module.h>
#include <linux/jiffies.h>
#include <linux/delay.h>

MODULE_AUTHOR("Mohamed Thalib H <hmthalib.gmail.com>");
MODULE_DESCRIPTION("Jiffies demo module");
MODULE_LICENSE("GPL");


int __init jif_init(void)
{

	return 0;
}


void __exit jif_exit(void) 
{

	
}

module_init(jif_init);
module_exit(jif_exit);
