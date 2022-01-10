#include<linux/module.h>
#include<linux/init.h>
#include<linux/moduleparam.h>

int addsym(int a, int b)
{

return(a+b);

}

EXPORT_SYMBOL_GPL(addsym);

int add_init(void)
{
printk(KERN_INFO "initialising add module\n");
return 0;
}

void  add_exit(void)
{
printk(KERN_INFO "cleaning up the add module\n");
}

module_init(add_init);
module_exit(add_exit);

MODULE_LICENSE("GPL");

