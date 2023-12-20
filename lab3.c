#include<linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h> 
#include<linux/proc_fs.h>
#include<linux/uaccess.h>
#include <linux/version.h>

#define procfs_name "tsu"
static struct proc_dir_entry *our_proc_file = NULL;

int init_module(void) {
pr_info("Welcome to Tomsk! Be healthy!\n");
return 0;
}
void cleanup_module(void) {
pr_info("Bye! Always dress according to the weather!\n");
}

MODULE_LICENSE("GPL");
