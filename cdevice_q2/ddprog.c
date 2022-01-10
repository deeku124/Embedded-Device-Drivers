#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include<linux/module.h>

#define name cdevice

int name_open(struct inode *inode,struct file *filp);
int name_release(struct inode *inode,struct file *filp);
ssize_t name_read(struct file *filp,char __user *Ubuff,size_t count,loff_t *offp);
ssize_t name_write(struct file *filp,const char __user *Ubuff,size_t count,loff_t *offp);

struct file_operations fops =
{   
    .owner = THIS_MODULE,
    .open = name_open,
    .release = name_release,
    .read = name_read,
    .write = name_write
};

struct cdev *my_cdev;

static int chdev_init(void)
{
    int result;
    int major,minor;
    dev_t device;
    device=MKDEV(255,0);
    major =MAJOR(device);
    minor= MINOR(device);
    printk(KERN_ALERT "the major and minor numbers of device are %d %d",major,minor);
    result=register_chrdev_region(device,1,"cdevice");
    if(result<0)
    {
        printk(KERN_ALERT "THE DEVICE REGION IS NOT AVAILABLE\n");
        return(-1);
    }
    my_cdev = cdev_alloc();
    my_cdev->ops = &fops;


    result=cdev_add(my_cdev,device,1);
    if(result<0)
    {
        printk(KERN_ALERT "the device is not added to the kernel\n");
        unregister_chrdev_region(device,1);
        return(-1);
    }
    printk(KERN_ALERT "the device has been successfully added to the kernel\n");
    return 0;
}


static void chdev_exit(void)
{
    int major,minor;
    dev_t device;
    device=MKDEV(255,0);
    major =MAJOR(device);
    minor= MINOR(device);
    printk(KERN_ALERT "the major and minor numbers of device are %d %d",major,minor);
    printk(KERN_ALERT "unregistering the device\n");
    unregister_chrdev_region(device,1);
    printk(KERN_ALERT "deleting the device\n");
    cdev_del(my_cdev);
}

int name_open(struct inode *inode,struct file *filp)
{
    printk(KERN_ALERT "you opened the device drive program.NICE TO MEET YOU\n");
    return 0;
}

int name_release(struct inode *inode,struct file *filp)
{
    printk(KERN_ALERT "you closed the device driver program.BYE BYE");
    return 0;
}

ssize_t name_read(struct file *filp,char __user *Ubuff,size_t count,loff_t *offp)
{
    char Kbuff[50]="nice to meet you user..how have u been?";
    unsigned long result;
    ssize_t retn;
    result=copy_to_user((char *)Ubuff,(char *)Kbuff,count);
    if(result==0)
    {
        printk(KERN_ALERT "entire data has been received successfully");
        return 0;
    }
    else if(result>0)
    {
        printk(KERN_ALERT "part of the data has been received\n");
        retn=count-result;
        return retn;
    }
    else
    {
        printk(KERN_ALERT "there has been an error\n");
        retn=-EFAULT;
        return retn;
    }
}


ssize_t name_write(struct file *filp,const char __user *Ubuff,size_t count,loff_t *offp)
{
    char Kbuff[50];
    unsigned long result;
    ssize_t retn;
    result=copy_from_user((char *)Kbuff,(char *)Ubuff,count);
    if(result==0)
    {
        printk(KERN_ALERT "the data has been written successfully\n");
        return 0;
    }
    else if(result>0)
    {
        printk(KERN_ALERT "part of the data has been written\n");
        retn=count-result;
        return retn;
    }
    else
    {
        printk(KERN_ALERT "error in writing the data\n");
        retn=-EFAULT;
        return retn;
    }
}
module_init(chdev_init);
module_exit(chdev_exit);