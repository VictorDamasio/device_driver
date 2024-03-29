# If KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can use its language.
##ifneq ($(KERNELRELEASE),)
## obj-m := my_driver.o
# Otherwise we were called directly from the command
# line; invoke the kernel build system.
##else
## KERNELDIR ?= /lib/modules/$(shell uname -r)/build
## PWD := $(shell pwd)
##default:
##	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
##endif

obj-m += my_driver.o

all:
	 make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	 $(CC) testDrive.c -o testDrive
clean:
	 make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	 rm testDrive
