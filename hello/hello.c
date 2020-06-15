#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include <linux/seq_file.h>

MODULE_LICENSE("Dual BSD/GPL");

int hello_count = 0;

int	hello_proc_read (struct seq_file *s, void *v)
{
    sprintf(v, "hello_count:%d\n", hello_count);
    printk(KERN_ALERT "Hello Count PRINT! BY ZICHEN LIU");
    return 0;
}

ssize_t hello_proc_write (struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{
    if(size > 0) {
        if(__get_user(hello_count, (int __user *)buf))
            return -EFAULT;
        printk(KERN_ALERT "Hello Count changed! BY ZICHEN LIU");
    }
    return size;
}

static int hello_open(struct inode *inode, struct file *file)
{
	return single_open(file, hello_proc_read, NULL);
}

static struct proc_ops hello_proc_ops = {
    .proc_open    = hello_open,
	.proc_read    = seq_read,
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
    remove_proc_entry("hello", NULL /* parent dir */);
    // printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);