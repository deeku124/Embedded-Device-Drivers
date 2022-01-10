#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>

int add(int a,int b)
{
return(a+b);
}
EXPORT_SYMBOL_GPL(add);
static int add_init(void)
{
printk(KERN_ALERT "initialising add module\n");
return 0;
}
static void add_exit(void)
{
printk(KERN_ALERT "cleaning up add module\n");
}
module_init(add_init);
module_exit(add_exit);

MODULE_LICENSE("GPL");
