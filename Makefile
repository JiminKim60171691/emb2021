obj-m := hello_drv2.o
KDIR := ../linux_kernel
PWD := $(shell pwd)
export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabi-

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	$(CROSS_COMPILE)gcc ./hello_test2.c -o drvtest2.elf
	scp *.ko ecube@192.168.0.7:/home/ecube/
	scp *.elf ecube@192.168.0.7:/home/ecube/
clean:
	-rm -f *.ko *.mod.c.*.cmd modules.order Module.symvers
	-rm -f *.o

