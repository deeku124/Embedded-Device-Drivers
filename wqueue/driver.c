#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/module.h>
#include<linux/wait.h>
#include<linux/kdev_t.h>

#define name cdevice

dev_t device;
char Kbuff[20];
int flag=1;
DECLARE_WAIT_QUEUE_HEAD(queue);

int name_open(struct inode *inode,struct file *filp);
int name_release(struct inode *inode,struct file *filp);
ssize_t name_read(struct file*filp,char __user *Ubuff,size_t count,loff_t *offp);
ssize_t name_write(struct file*filp,const char __user *Ubuff,size_t count,loff_t *offp);

struct file_operations fops =
{
    .open = name_open,
    .release = name_release,
    .read = name_read,
    .write = name_write
};

struct cdev *my_cdev;

static int chdev_init(void)
{
    int major,minor;
    int result;
    result=alloc_chrdev_region(&device,0,1,"cdevice");
    if(result<0)
    {
        printk(KERN_ALERT "this device region cannot be allocated\n");
        return (-1);
    }
    major=MAJOR(device);
    minor=MINOR(device);
    printk(KERN_ALERT "the major and minor number of device is %d %d",major,minor);
    
    my_cdev = cdev_alloc();
    my_cdev->ops = &fops;
    //cdev_init(my_cdev,&fops);

    result=cdev_add(my_cdev,device,1);
    if(result<0)
    {
        printk(KERN_ALERT "this device is not added to the kernel\n");
        unregister_chrdev_region(device,1);
        return(-1);
    }
    printk(KERN_ALERT "the device has been successfully added to the kernel\n");
    return 0;
}

static void chdev_exit(void)
{
    int major,minor;
    //flag=3;
    major=MAJOR(device);
    minor=MINOR(device);
    printk(KERN_ALERT "the major and minor number of device is %d %d",major,minor);
    printk(KERN_ALERT "UNREGISTERING THE DEVICE\n");
    unregister_chrdev_region(device,1);
    cdev_del(my_cdev);
    printk(KERN_ALERT "DELETING THE DEVICE\n");
   
}

int name_open(struct inode *inode,struct file *filp)
{
    printk(KERN_ALERT "opening the driver...\n");
    return 0;
}

int name_release(struct inode *inode,struct file *filp)
{
    printk(KERN_ALERT "closing the driver\n");
    return 0;
}

ssize_t name_read(struct file *filp,char __user *Ubuff,size_t count,loff_t *offp)
{
    ssize_t retn;
    unsigned long result;
    result=copy_to_user((char *)Ubuff,(char *)Kbuff,count);
    flag=1;
    wake_up(&queue);
    if(result==0)
    {
        printk(KERN_ALERT "entire data has been successfully read\n");
        return 0;
    }
    else if(result>0)
    {
        printk(KERN_ALERT "part of the data has been successfully read\n");
        retn=count-result;
        return retn;
    }
    else
    {
        printk(KERN_ALERT "error reading data from kernel\n");
        retn=-EFAULT;
        return retn;
    }
}


ssize_t name_write(struct file *filp,const char __user *Ubuff,size_t count,loff_t *offp)
{
    
    ssize_t retn;
    unsigned long result;
    wait_event(queue,flag==1);
    /*if(flag==3)
    {
        printk(KERN_ALERT"event came from exit function\n");
        flag++;
    }*/
    result=copy_from_user((char *)Kbuff,(char *)Ubuff,count);
    printk(KERN_ALERT "data written is %s\n",Kbuff);
    flag++;
    
    if(result==0)
    {
        printk(KERN_ALERT "entire data has been successfully written\n");
        return 0;
    }
    else if(result>0)
    {
        printk(KERN_ALERT "part of the data has been successfully written\n");
        retn=count-result;
        return retn;
    }
    else
    {
        printk(KERN_ALERT "error writing data to the kernel\n");
        retn=-EFAULT;
        return retn;
    }
    
}

module_init(chdev_init);
module_exit(chdev_exit);