#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/rtnetlink.h>

struct net_device *my_dev;


static int mynet_setmac(struct net_device *dev, void *p)
{
	// dummy
	return 0;
	
}

static void set_multicast_list(struct net_device *dev)
{
	// dummy
}

static int mynet_xmit(struct sk_buff *skb,struct net_device *dev)
{
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;
	
	dev_kfree_skb(skb);
	
	return NETDEV_TX_OK;
}

static struct net_device_ops mynet_ops = {
	.ndo_start_xmit = mynet_xmit,
	.ndo_validate_addr = eth_validate_addr,
	.ndo_set_multicast_list = set_multicast_list,
	.ndo_set_mac_address = mynet_setmac,
};

static void mynet_setup(struct net_device *dev)
{
	ether_setup(dev);
	dev->netdev_ops = &mynet_ops;
	dev->destructor = free_netdev;
	
	dev->tx_queue_len = 0;
	dev->flags |= IFF_NOARP;
	dev->flags &= ~IFF_MULTICAST;
	
	random_ether_addr(dev->dev_addr);
	
}

static int mynet_validate(struct nlattr *tb[], struct nlattr *data[])
{
/* 	if (tb[IFLA_ADDRESS]) { */
/* 		if (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN) */
/* 			return -EINVAL; */
/* 		if (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS]))) */
/* 			return -EADDRNOTAVAIL; */
/* 	} */
	return 0;
}

/* static struct rtnl_link_ops dummy_link_ops __read_mostly = { */
/* 	.kind		= "dummy", */
/* 	.setup		= dummy_setup, */
/* 	.validate	= dummy_validate, */
/* }; */


					    
static struct rtnl_link_ops link_ops __read_mostly = {
	.kind = "mynet",
	.setup = mynet_setup,
	.validate = mynet_validate,
};

int __init mynet_init(void)
{
	
	int err;

	my_dev = alloc_netdev(0, "mynet", mynet_setup);

	if (!my_dev) {
		printk("alloc_netdev failed\n_");
		return -ENOMEM;
	}
	printk("alloc_netdev succeded\n");
	err = dev_alloc_name(my_dev, my_dev->name);
	if(err) 
		goto err;

	printk("dev_alloc_name succedded \n");
	
	my_dev->rtnl_link_ops = &link_ops;
	
	err = register_netdevice(my_dev);
	
	if(err) 
		goto err;


	printk("register_netdevice succedded \n");
	return 0;

  err:
	free_netdev(my_dev);
	return err;
}

void __exit mynet_exit(void)
{

	
}

MODULE_AUTHOR("Mohamed Thalib H <hmthalib@gmail.com>");
MODULE_DESCRIPTION("MY NET MODULE");
MODULE_LICENSE("GPL");


module_init(mynet_init);
module_exit(mynet_exit);
