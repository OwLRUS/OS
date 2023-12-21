#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/version.h>
#include <linux/ktime.h>
#include <linux/time64.h>

#define procfs_name "tsulab"
static struct proc_dir_entry* our_proc_file = NULL;

static ssize_t procfile_read(struct file* file_pointer,
    char __user* buffer, size_t buffer_length, loff_t* offset) {

    s64 maya_start_sec = 1356037200;

    struct timespec64 current_time;
    ktime_get_real_ts64(&current_time);

    s64 diff_seconds = current_time.tv_sec - maya_start_sec;

    int days_passed = diff_seconds / (60 * 60 * 24);

    char s[64];
    ssize_t ret;

    ret = sprintf(s, "Days since Mayan calendar start: %d", days_passed);

    if (*offset >= ret || copy_to_user(buffer, s, ret)) {
        ret = 0;
    }
    else {
        pr_info("procfile was read on %s\n", file_pointer->f_path.dentry->d_name.name);
        *offset += ret;
    }

    return ret;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0)
static const struct proc_ops proc_file_fops = {
    .proc_read = procfile_read,
};
#else
static const struct file_operations proc_file_fops = {
    .read = procfile_read,
};
#endif

static int __init procfs1_init(void) {
    our_proc_file = proc_create(procfs_name, 0644, NULL, &proc_file_fops);
    if (NULL == our_proc_file) {
        pr_alert("Error:Could not initialize /proc/%s\n", procfs_name);
        return -ENOMEM;
    }

    pr_info("proc %s was created\n", procfs_name);
    return 0;
}

static void __exit procfs1_exit(void) {
    proc_remove(our_proc_file);
    pr_info("proc %s was removed\n", procfs_name);
}

module_init(procfs1_init);
module_exit(procfs1_exit);
MODULE_LICENSE("GPL");