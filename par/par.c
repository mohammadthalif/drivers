#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>

#include <asm/io.h>

MODULE_AUTHOR("Mohamed Thalib H <h.mohamedthalib@gdatech.co.in>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Parallel port Demo");

#define BASE 0x378
#define NR_PORTS 1

int __init pa_init(void)
{
	u8 buff;
	printk(KERN_INFO "%s: loaded\n", __FUNCTION__);

	if(! request_region(BASE, NR_PORTS, "par")) {
		printk(KERN_INFO "%s: reqest region failed\n", __FUNCTION__);
	}

	buff = inb(BASE);
	rmb();

	printk(KERN_INFO "%s: buff = %d\n", __FUNCTION__, buff);

	
	return 0;
}

void __exit pa_exit(void)
{
	printk(KERN_INFO "%s: unloaded\n", __FUNCTION__);

	release_region(BASE, NR_PORTS);
}

module_init(pa_init);
module_exit(pa_exit);

