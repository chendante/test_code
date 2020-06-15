#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/errno.h>
#include <linux/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

int hello_count = 0;

ssize_t	hello_proc_read (struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
    sprintf(buf, "hello_count:%d\n", hello_count);
    printk(KERN_ALERT "Hello Count PRINT! BY ZICHEN LIU")
    return strlen(buf);
}

ssize_t hello_proc_write (struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{
    if(len > 0) {
        if(__get_user(hello_count, (int __user *)buf))
            return -EFAULT;
        printk(KERN_ALERT "Hello Count changed! BY ZICHEN LIU");
    }
    return len;
}

static struct proc_ops scullmem_proc_ops = {
	.proc_read    = hello_proc_read,
    .proc_write   = hello_proc_write
};

static int hello_init(void)
{
    // printk(KERN_ALERT "Hello, world\n");
    proc_create("hello", 0 /* default mode */,
			NULL /* parent dir */, &hello_proc_ops);
    return 0;
}

static void hello_exit(void)
{
    // printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);