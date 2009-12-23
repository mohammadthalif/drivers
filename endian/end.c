#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/byteorder.h>

MODULE_AUTHOR("Mohamed Thalib H <h.mohamedthalib@gdatech.co.in>");
MODULE_DESCRIPTION("Endians example module");
MODULE_LICENSE("GPL");


int __init end_init(void)
{

	u32 a, b;
	a = 10;
	
	b=cpu_to_be32(a);
	
	printk("%d\n",a);
	printk("%d\n",b);
	printk("%d\n",be32_to_cpu(b));


#ifdef __BIG_ENDIAN
	printk("this is a big endian machine \n");
#elif __LITTLE_ENDIAN
	printk("this is a little endian machine \n");
#endif


	return 0;
}

void __exit end_exit(void)
{


}

module_init(end_init);
module_exit(end_exit);
