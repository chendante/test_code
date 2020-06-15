#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

int b;

static int hello_init(void)
{
    int a = 0;
    b = a + 1;
    
    return 0;
}

static void hello_exit(void)
{
    b = b + 2;
}

module_init(hello_init);
module_exit(hello_exit);