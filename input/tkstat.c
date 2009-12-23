#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/input.h>


static struct input_dev dev {

};


int __init tkstat_init(void)
{

}

void __exit tkstat_exit(void)
{


}


MODULE_AUTHOR("Mohamed Thalib H");
MODULE_DESCRIPTION("Keyboard status LED Demo");
MODULE_LICENSE("GPL");

module_init(tkstat_init);
module_exit(tkstat_exit);
