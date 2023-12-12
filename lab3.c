#include<linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h> 
#include<linux/proc_fs.h>
#include<linux/uaccess.h>
#include <linux/version.h>

int init_module(void) {
pr_info("Welcome to the Tomsk State University\n");
return 0;
}
void cleanup_module(void) {
pr_info("Tomsk State University forever!\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Brits V");
MODULE_DESCRIPTION("A simple kernel module");
