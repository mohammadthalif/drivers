obj-m := mynet.o

#KERNELDIR = /usr/src/linux-headers-2.6.31-14-generic/
KERNELDIR = /usr/src/linux-source-2.6.31

PWD:= $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

.PHONY=clean

clean:
	-@rm -rf *.o *.ko Module.symvers *~ *.mod.* .*.cmd
	-@rm -rf .tmp_versions *.cmd  modules.order

