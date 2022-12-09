#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define MY_FILE "/tmp/log.txt"

char buf[256];
loff_t pos = 0;
struct file *filep = NULL;

static int __init kernel_wr_rd_init(void)
{
    printk("Hello, I'm the module that intends to write messages to file.\n");

    if(filep == NULL) {
            filep = filp_open(MY_FILE, O_RDWR | O_APPEND | O_CREAT, 0644);
    }

    if (IS_ERR(filep)) {
            printk("Open file %s error\n", MY_FILE);
            return -1;
    }

    memset(buf, 0, sizeof(buf));
    sprintf(buf,"%s\n", "This is test message!");
    kernel_write(filep, buf, sizeof(buf), &pos);

    pos = 0;
    memset(buf, 0, sizeof(buf));
    kernel_read(filep, buf, sizeof(buf), &pos);
    printk("Read buf -> %s\n", buf);

    return 0;
}

static void __exit kernel_wr_rd_exit(void)
{
    printk("Kernel read/write exit\n");

    if(filep != NULL) {
            filp_close(filep, NULL);
    }
}

module_init(kernel_wr_rd_init);
module_exit(kernel_wr_rd_exit);
MODULE_LICENSE("GPL");
