##ifneq
	obj-m := driver.o
##elseif
	KDIR= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules
	gcc -o usr1 usr1.c
	gcc -o usr2 usr2.c
	gcc -o usread usread.c
clean:
	make -C $(KDIR) M=$(PWD) clean
	rm usr1
	rm usr2
	rm usread
#endif
