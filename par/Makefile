obj-m := par.o

KERNELDIR = /usr/src/linux


PWD:= $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

.PHONY=clean
clean:
	-@rm -rf *.o *.ko Module.symvers *~ *.mod.* .*.cmd
	-@rm -rf .tmp_versions *.cmd  modules.order

