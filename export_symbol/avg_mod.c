#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include "addsym.h"

static int avg_init(void)
{
int avg;
avg=addsym(12,18)/2;
printk(KERN_INFO "initialising avg module\n");
printk(KERN_INFO "sum of two numbers is %d\n",addsym(12,18));
printk(KERN_INFO "avg of two numbers is %d\n",avg);
return 0;
}
static void avg_exit(void)
{
printk(KERN_INFO "cleaning up the avg module\n");
}
module_init(avg_init);
module_exit(avg_exit);

MODULE_LICENSE("GPL");