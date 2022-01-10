obj-m :=  avg_mod.o ../add_mod/add_mod.o

KERNELDIR= /lib/modules/$(shell uname -r)/build/

PWD := $(shell pwd)

default:
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	make -C $(KERNELDIR) M=$(PWD) clean
	rm -rf /lib/modules/$(shell uname -r)/build/extra/*

install:
	make -C $(KERNELDIR) M=$(PWD) modules_install
	depmod -a
