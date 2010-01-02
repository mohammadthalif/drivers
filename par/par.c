#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/ioport.h>

#include <asm/io.h>

MODULE_AUTHOR("Mohamed Thalib H <h.mohamedthalib@gdatech.co.in>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Parallel port Demo");

int par_major = 200;
int par_minor;
unsigned long base = 0x378;
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
	static int tog = 0;
	static unsigned char data = 0;
	unsigned long port = base + (par_minor&0x0f);

	printk(KERN_INFO "par: device opened, tog = %d, data = %x\n", tog,data);

	if (tog) {
		outb(data, port);
		wmb();
	} else {
		outb(data, port);
		wmb();
	}

	tog ^= 1;
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
		
	if(!request_region(base, 4, "par")) {
		printk(KERN_INFO "par: err while request_region()\n");
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

	 release_region(base, 4);
}


module_init(par_init);
module_exit(par_exit);
