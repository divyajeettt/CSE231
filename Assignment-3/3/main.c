#include <linux/pid.h>
#include <linux/init.h>
#include <linux/cred.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>


static int param_pid = 0;
module_param(param_pid, int, S_IRUSR|S_IWUSR);


void sys_read_task_struct(void)
{
    struct task_struct *task = pid_task(find_vpid(param_pid), PIDTYPE_PID);
    printk("pid: %d \n", task->pid);
    printk("user_id: %d\n", task->cred->uid);
    printk("process group id: %d \n", task->tgid);
    printk("community path: %s \n", task->comm);
}


static int __init sys_read_task_struct_init(void)
{
    printk(KERN_INFO "init invoked [run: param_pid = %d] \n", param_pid);
    sys_read_task_struct();
    return 0;
}


static void __exit sys_read_task_struct_exit(void)
{
    printk(KERN_INFO "exit invoked \n");
}


module_init(sys_read_task_struct_init);
module_exit(sys_read_task_struct_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("dvgt");
MODULE_DESCRIPTION("Kernel Module implemented for CSE231 Assignment-3");