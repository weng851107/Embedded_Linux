#include <linux/init.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/vmalloc.h>
#include <linux/math64.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/delay.h>
#include <linux/list.h>
#include <linux/random.h>
#include <linux/sched.h>
#include <linux/sched/mm.h>
#include <linux/fs.h>
#include <linux/pagemap.h>
#include <linux/seq_file.h>
#include <linux/debugfs.h>

static char *cache_file = "/home/chicony/hwaddr.txt";

static int __init kernel_read_init(void)
{
	struct file *cfile;
	int err;
	ssize_t rx;
	loff_t pos = 0;
	char tmp_char[32];
    char mac[6][5];
	size_t count;
	void *buf;

	memset(tmp_char, 0, sizeof(tmp_char));

	if (cache_file) {
		cfile = filp_open(cache_file, O_CREAT | O_RDWR, 0664);
		if (IS_ERR(cfile)) {
			printk("%s, %s open failed\n", __func__, cache_file);
			// return PTR_ERR(cfile);
			return;
		}

		if (!(cfile->f_mode & FMODE_CAN_READ)) {
			printk("%s, %s not readable\n", __func__, cache_file);
			err = -EINVAL;
			goto err_close_filp;
		}

		printk("%s, before read tmp_char: rx %lld, pos %lld\n", __func__, rx, pos);
		count = sizeof(tmp_char);
		buf = (void *)tmp_char;
		rx = kernel_read(cfile, buf, count, &pos);
		printk("%s, after read tmp_char: rx %lld, pos %lld\n", __func__, rx, pos);		
		printk("%s, read result: tmp_char=%s\n", __func__, tmp_char);
        
        int i;
        for(i = 0;i < 6;i++){
            mac[i][0] = tmp_char[5*i];
            mac[i][1] = tmp_char[5*i + 1];
            mac[i][2] = tmp_char[5*i + 2];
            mac[i][3] = tmp_char[5*i + 3];
            mac[i][4] = '\0';
        }
        printk("%s, read result: mac[0]=%s\n", __func__, mac[0]);
        printk("%s, read result: mac[1]=%s\n", __func__, mac[1]);
        printk("%s, read result: mac[2]=%s\n", __func__, mac[2]);
        printk("%s, read result: mac[3]=%s\n", __func__, mac[3]);
        printk("%s, read result: mac[4]=%s\n", __func__, mac[4]);
        printk("%s, read result: mac[5]=%s\n", __func__, mac[5]);

err_close_filp:
		filp_close(cfile, NULL);
	}
}

static void kernel_read_exit(void)
{

}

module_init(kernel_read_init);
module_exit(kernel_read_exit);

MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("AntonyWeng");
MODULE_DESCRIPTION ("kernel read module");