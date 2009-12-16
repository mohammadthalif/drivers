#include <linux/module.h>
#include <linux/init.h>
#include <linux/i2c.h>


MODULE_AUTHOR("Mohamed Thalib H <h.thalib@gmail.com>");
MODULE_DESCRIPTION("Sample I2C driver");
MODULE_LICENSE("GPL");

int ti2c_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs, int num)
{

	printk("%s : %s called", __FILE__, __FUNCTION__);

	return 0;
}

static u32 fun (struct i2c_adapter *adap)
{
	return  I2C_FUNC_I2C;
}

static struct i2c_algorithm algo = {
	.master_xfer = &ti2c_xfer,
	.functionality = &fun
};

static struct i2c_adapter adap  = {
	.owner = THIS_MODULE,
	.algo = &algo,	
	.timeout = 100,
	.name = "Thalib I2C",
};

int __init ti2c_init(void)
{
	u32 result;
	
	printk("ti2c: init\n");
	
	result = i2c_add_adapter(&adap);
	
	if(0>result) {
		printk(KERN_ERR "Adding thalib i2c adapter failed: %d \n", result);
	}
	
	printk(KERN_ERR "Adding thalib i2c adapter success: %d \n", result);

	return result;

}

void __exit ti2c_exit(void)
{
	i2c_del_adapter(&adap);
	printk("ti2c: exit\n");
}


module_init(ti2c_init);
module_exit(ti2c_exit);
