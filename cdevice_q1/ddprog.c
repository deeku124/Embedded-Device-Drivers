#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/module.h>

#define name MyCharDevice

int name_open(struct inode *inode,struct file *filp);
int name_release(struct inode *inode,struct file *filp);
ssize_t name_read(struct file *filp,char __user *Ubuff,size_t count,loff_t *offp);
ssize_t name_write(struct file *filp,const char __user *Ubuff,size_t count,loff_t *offp);


struct file_operations fops =
{
.owner = THIS_MODULE,
.open = name_open,
.release = name_release
};

struct cdev *my_cdev;

static int chardev_init(void)
{
int result;
int major,minor;
dev_t device;
device=MKDEV(255,0);
major=MAJOR(device);
minor=MINOR(device);
printk(KERN_ALERT "the major and minor numbers of my charecter device is %d,%d\n",major,minor);
result=register_chrdev_region(device,1,"MyCharDevice");
if(result<0)
{
printk(KERN_ALERT "the device region is not allocated\n");
return(-1);
}

my_cdev = cdev_alloc();
my_cdev->ops = &fops;

result=cdev_add(my_cdev,device,1);
if(result<0)
{
printk(KERN_ALERT "device is not added to the kernel\n");
unregister_chrdev_region(device,1);
return(-1);
}
printk(KERN_ALERT "the device has been successfully added to the kernel\n");
return 0;
}


static void chardev_exit(void)
{
dev_t device;
int major,minor;
device=MKDEV(255,0);
major=MAJOR(device);
minor=MINOR(device);
printk(KERN_ALERT "the major and minor numbers of my charecter device is %d,%d\n",major,minor);
printk(KERN_ALERT "unregistering the device\n");
unregister_chrdev_region(device,1);
cdev_del(my_cdev);
printk(KERN_ALERT "deleting the device\n");
}



int name_open(struct inode *inode,struct file *filp)
{
printk(KERN_ALERT "opening the charecter device, iam bored\n");
return 0;
}

int name_release(struct inode *inode,struct file *filp)
{
printk(KERN_ALERT "closing the file because iam bored\n");
return 0;
}


module_init(chardev_init);
module_exit(chardev_exit);