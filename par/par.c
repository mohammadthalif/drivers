#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/ioport.h>
#include <linux/pnp.h>

#include <asm/io.h>

#define BASE 0x378
#define NR_COUNT 3

MODULE_AUTHOR("Mohamed Thalib H <h.mohamedthalib@gdatech.co.in>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Parallel port Demo");

int par_major = 200;
int par_minor;



static struct cdev par_dev;


static ssize_t par_read(struct file *fp, char *buff, size_t len, loff_t *off)
{
	return 0;
}
static ssize_t par_write(struct file *fp, const char *buff, size_t len, loff_t *off)
{
	return 0;
}


static int par_ioctl(struct inode *inode, struct file *fp, unsigned int cmd, unsigned long arg)
{
	return 0;
}

static int par_open(struct inode *node, struct file *fp)
{
	static u8 data = 0;
	u8 i;
	u8 buff;

	for(i=1; i<=0xff; i<<=1) { 
		barrier();
		outb(i,BASE); 
		wmb();
		buff = inb(BASE);
		rmb();
		ssleep(1);
		printk(KERN_INFO "par: device opened, data = 0x%x, BASE=0x%x, \
buff=%d \n", i, (unsigned int) BASE, buff);
	
		data ^= 0xff;

		if(i == 0)
			break;
	}
	return 0;
}

static int par_release(struct inode *inode, struct file *fp)
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

static int par_register(void)
{
	dev_t dev;
	int ret;

	if(! request_region((unsigned long) BASE, NR_COUNT, "par")) {
		printk(KERN_INFO "par: error cant get IOmem addr 0x%1x\n", \
		       (unsigned int) BASE);
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

	outb(0xFF,BASE); 
	wmb();

	printk(KERN_INFO "par: device registerd\n");

	return 0;

  exit_1:
	unregister_chrdev_region(dev, 1);
  exit_out:
	return ret;
	
}

#ifdef CONFIG_PNP

static const struct pnp_device_id par_pnp_tbl[] = {
	/* Standard LPT Printer Port */
	{.id = "PNP0400", .driver_data = 0},
	{ }
};

MODULE_DEVICE_TABLE(pnp, par_pnp_tbl);

static int par_pnp_probe(struct pnp_dev *dev, const struct pnp_device_id *id)
{
	
	unsigned long io_lo;

	if (pnp_port_valid(dev, 0) && 
	    !(pnp_port_flags(dev, 0) & IORESOURCE_DISABLED)) {
		io_lo = pnp_port_start(dev, 0);
	} else
		return -EINVAL;

	dev_info(&dev->dev, "reported by %s\n", dev->protocol->name);

	return 0;
}

static void par_pnp_remove(struct pnp_dev *dev)
{
	/* nothing to do in remove */
}

/* we only need the pnp layer to activate the device, at least for now */
static struct pnp_driver par_pnp_driver = {
	.name		= "par",
	.id_table	= par_pnp_tbl,
	.probe		= par_pnp_probe,
	.remove		= par_pnp_remove,
};

#endif /* CONFIG_PNP */




int __init par_init(void)
{
	int ret;

	printk(KERN_INFO "par: parlell port demo\n");

#ifdef CONFIG_PNP
	
	ret = pnp_register_driver(&par_pnp_driver);
	
	if (!ret) {
		printk(KERN_INFO "par: pnp device registered\n");
	} else {
		printk(KERN_INFO "par: pnp device registration failed\n");
		return ret;
	}
	
#endif	
	ret = par_register();

	return ret;
}


void __exit par_exit(void)
{

	dev_t dev = MKDEV(par_major, par_minor);

	printk(KERN_INFO "par: cdev_del()\n");
	cdev_del(&par_dev);

	printk(KERN_INFO "par: unregister_chrdev_region()\n");
	unregister_chrdev_region(dev, 1);

	release_region(BASE, NR_COUNT);
	 
	pnp_unregister_driver(&par_pnp_driver);
		
}


module_init(par_init);
module_exit(par_exit);
