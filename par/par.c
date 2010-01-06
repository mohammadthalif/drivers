#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
<<<<<<< HEAD:par/par.c
#include <linux/ioport.h>
#include <linux/interrupt.h>
=======
#include <linux/fs.h>
#include <linux/ioport.h>
>>>>>>> 89700407e98fc216012562a792414d95e9e4a758:par/par.c

#include <asm/io.h>

MODULE_AUTHOR("Mohamed Thalib H <h.mohamedthalib@gdatech.co.in>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Parallel port Demo");

<<<<<<< HEAD:par/par.c
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
=======
int par_major = 200;
int par_minor;
unsigned long base = 0x0378;
unsigned int reg_count = 1;
static struct cdev par_dev;


ssize_t par_read(struct file *fp, char *buff, size_t len, loff_t *off)
{
	return 0;
}
ssize_t par_write(struct file *fp, const char *buff, size_t len, loff_t *off)
{
	return 0;
}


int par_ioctl(struct inode *inode, struct file *fp, unsigned int cmd, unsigned long arg)
{
	return 0;
}

int par_open(struct inode *node, struct file *fp)
{
	static unsigned char data = 0;
	u8 buff;

	barrier();
	outb(base); 
	buff = inb(base);
	rmb();

	printk(KERN_INFO "par: device opened, data = 0x%x, base=0x%x, \
buff=%d \n", data, (unsigned int) base, buff);
	
	data ^= 0xff;

	return 0;
}

int par_release(struct inode *inode, struct file *fp)
{
	printk(KERN_INFO "par: device closed\n");
	return 0;
}


static struct file_operations par_ops = {
	.owner = THIS_MODULE,
	.ioctl = par_ioctl,
	.open = par_open,
	.release = par_release,
	.read = par_read,
	.write = par_write
};

int __init par_init(void)
{
	u32 ret;
	dev_t dev;

	printk(KERN_INFO "par: parlell port demo\n");

	if(!check_region(base, reg_count)){
		printk(KERN_INFO "par: check_region failed\n");
	}
	
	if(! request_region(base, reg_count, "par")) {
		printk(KERN_INFO "par: error cant get IOmem addr 0x%1x\n", (unsigned int) base);
		return -ENODEV;
	}


	dev = MKDEV(par_major, par_minor);

	ret = register_chrdev_region(dev, 1, "par");
	if (0 > ret) {
		printk(KERN_INFO "par: erro while register_chrdev_region()\n");
		goto exit_out;
	}

	cdev_init(&par_dev, &par_ops);
	ret =  cdev_add(&par_dev, dev, 1);
	if (0 > ret) {
		printk(KERN_INFO "par: cdev_add() error\n");
		goto exit_1;
	}

	return 0;

exit_1:
	unregister_chrdev_region(dev, 1);
exit_out:
	return ret;
}


void __exit par_exit(void)
{

	 dev_t dev = MKDEV(par_major, par_minor);

	 printk(KERN_INFO "par: cdev_del()\n");
	 cdev_del(&par_dev);

	 printk(KERN_INFO "par: unregister_chrdev_region()\n");
	 unregister_chrdev_region(dev, 1);

	 release_region(base, reg_count);
>>>>>>> 89700407e98fc216012562a792414d95e9e4a758:par/par.c
}

module_init(pa_init);
module_exit(pa_exit);

module_init(par_init);
module_exit(par_exit);
