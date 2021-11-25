#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define HELLO_MAJOR_NUM 290
#define HELLO_NAME "hello"

char arrData[4] = 0;

static int hello_open(struct inode *inode, struct file *pfile)
{
    printk("hell_open enter\n");
    return 0;
}

static ssize_t hello_read(struct file *pfile, char *pBuff, size_t size, loff_t *fd)
{
    printk("hello_read enter\n");
    if(size >= 4)
    {
        copy_to_user(pBuff,arrData,4);
        return 4;
    }
    return 0;
}

static ssize_t hello_write(struct file *pfile, const char *pBuff, size_t size, loff_t *fd)
{
    printk("hello_write enter\n");
    if(size >= 4)
    {
        copy_from_user(pBuff,arrData,4);
        return 4;
    }
    return 0;
}

static int hello_release(struct inode *inode, struct file *pfile)
{
    printk("hell_release enter\n");
    return 0;
}

static const struct file_operations hello_fops ={
    .owner = THIS_MODULE,
    .open = hello_open,
    .read = hello_read,
    .write = hello_write,
    .release = hello_release,
};

int flagRegisterSuccess = 0;

int init_hello(void)
{
    int ret;
    printk("Hello world\n");
    ret = register_chrdev(HELLO_MAJOR_NUM, HELLO_NAME, &hello_fops);
    if(ret < 0)
    {
        printk("Hello register_chrdev fail\n");
        return ret;
    }
    flagRegisterSuccess = 1;
    return 0;
}

void exit_hello(void)
{
    if(flagRegisterSuccess)
    {
        flagRegisterSuccess = 0;
        register_chrdev(HELLO_MAJOR_NUM, HELLO_NAME);
    }
    printk("Good-bye~\n");
}

module_init(init_hello);
module_exit(exit_hello);

MODULE_LICENSE("GPL");