#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define HELLO_MAJOR_NUM 290
#define HELLO_NAME "hello"

static char arrData[2000];
int i = 0

static int hello_open(struct inode *inode, struct file *pfile)
{
    printk("hello_open enter\n");
    return 0;
}

static ssize_t hello_read(struct file *pfile, char *pBuff, size_t size, loff_t *fd)
{
    printk("hello_read enter\n");
    for(i=0;i<2000;i++)
    {
        put_user(arrData[i], pBuff);
        return i;
    }
    return 0;
}

static ssize_t hello_write(struct file *pfile, const char *pBuff, size_t size, loff_t *fd)
{
    printk("hello_write enter\n");
    for(i=0;i<2000;i++)
    {
        get_user(arrData[i], pBuff);
        return i;
    }
    return 0;
}

static int hello_release(struct inode *inode, struct file *pfile)
{
    printk("hello_release enter\n");
    return 0;
}

static long hello_ioctl(struct file *flip, unsigned int cmd, unsigned long arg)
{
    printk("hello_ioctl enter\n");
    if(_IOC_TYPE (cmd) != 0x55) {
        printk("wrong!!\n");
        return -1;
        }
    
    switch (_IOC_NR (cmd))
    {
    case 99:
        for(i=0;i<arg;i++)
        printk("%d", arrData[i]);
        printk("\n");
        break;
    
    default:
        break;
    }
)

static const struct file_operations hello_fops ={
    .owner = THIS_MODULE,
    .open = hello_open,
    .read = hello_read,
    .write = hello_write,
    .release = hello_release,
    .unlocked_ioctl = hello_ioctl,
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
        unregister_chrdev(HELLO_MAJOR_NUM, HELLO_NAME);
    }
    printk("Good-bye~\n");
}

module_init(init_hello);
module_exit(exit_hello);

MODULE_LICENSE("GPL");