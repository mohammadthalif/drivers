obj-m := par.o

<<<<<<< HEAD:par/Makefile
KERNELDIR = /usr/src/linux
=======
#KERNELDIR = /usr/src/linux-source-2.6.28/
>>>>>>> 89700407e98fc216012562a792414d95e9e4a758:par/Makefile
#KERNELDIR =  /home/thalib/host/linux-source-2.6.26
KERNELDIR = /usr/src/linux_old

PWD:= $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

.PHONY=clean
clean:
	-@rm -rf *.o *.ko Module.symvers *~ *.mod.* .*.cmd
	-@rm -rf .tmp_versions *.cmd  modules.order

