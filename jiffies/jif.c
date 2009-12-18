#include <linux/module.h>
#include <linux/jiffies.h>
#include <linux/delay.h>

MODULE_AUTHOR("Mohamed Thalib H <hmthalib.gmail.com>");
MODULE_DESCRIPTION("Jiffies demo module");
MODULE_LICENSE("GPL");


int __init jif_init(void)
{
	u32 vala, valb, ret;
	clock_t clk;
	vala = jiffies;
	ssleep(1);
	valb = jiffies;
	
	printk("vala = %d, valb = %d \n",vala, valb);
	
	ret = time_is_before_jiffies((unsigned long) valb) ;
	printk("ret = %d\n", ret);
	
	ret = time_is_after_jiffies((unsigned long) valb);
	printk("ret = %d\n", ret);


	ret = time_after((unsigned long) vala, (unsigned long) valb);
	printk("ret = %d\n", ret);

	clk = jiffies_to_clock_t(100);
	printk("jiffies to clock %d\n",(int)clk);

	ret = msecs_to_jiffies(100);
	printk("jiffies for msec = %d\n", ret);
	
	ret = jiffies_to_msecs(100);
	printk("msecs to jiffies = %d\n", ret);
	       

	ret = (unsigned long) usecs_to_jiffies(100);
	printk("jiffies for usec = %d\n", ret);
	
	ret = (unsigned long) jiffies_to_usecs(100);
	printk("usecs to jiffies = %d\n", ret);
	
	ret = time_before((unsigned long) vala, (unsigned long) valb);
	printk("time before = %d\n", ret);

	ret = time_in_range((unsigned long) vala, (unsigned long) valb, jiffies);
	printk("time in range = %d\n", ret);

	return 0;
}


void __exit jif_exit(void) 
{

	
}

module_init(jif_init);
module_exit(jif_exit);
