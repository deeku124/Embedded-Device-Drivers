#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include "add.h"

static int avg_init(void)
{
int avg;
avg=add(12,20)/2;
printk(KERN_ALERT "initialising avg module\n");
printk(KERN_ALERT "sum of two numbers is %d\n",add(12,20));
printk(KERN_ALERT "avg of two numbers is %d\n",avg);
return 0;
}
static void avg_exit(void)
{
printk("cleaning up avg modue\n");
}
module_init(avg_init);
module_exit(avg_exit);

MODULE_LICENSE("GPL");