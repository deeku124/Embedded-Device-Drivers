#include<linux/module.h>
#include<linux/init.h>

int hello_init(void)
{
        printk("hello world,i am a module\n");
        return 0;
}
void hello_exit(void)
{
        printk("BYE world,iam now not a module\n");
}
module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");


