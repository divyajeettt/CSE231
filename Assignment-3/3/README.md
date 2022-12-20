# Kernel Module

A loadable kernel module is an object file that contains code that can extend the kernel functionality at runtime. It is loaded as needed, and can be unloaded when the need finishes. Problem 3 required us to write a system call as a kernel module that would take as input the process ID of a process and display certain information about the process.

## Program Logic

The kernel module makes use of a global variable `param_pid` which holds the arguement passed to the module, and initialized to `0`. This is seen in code in `main.c` as follows:

```c
static int param_pid = 0;
module_param(param_pid, int, S_IRUSR|S_IWUSR);
```

The main function that prints the required fields from the task struct simply accesses the task struct associated with the `param_pid` and is as follows:

```c
void sys_read_task_struct(void)
{
    struct task_struct *task = pid_task(find_vpid(param_pid), PIDTYPE_PID);
    printk("pid: %d \n", task->pid);
    printk("user_id: %d\n", task->cred->uid);
    printk("process group id: %d \n", task->tgid);
    printk("community path: %s \n", task->comm);
}
```

The module is written with the following license, author, and description:

```c
MODULE_LICENSE("GPL");
MODULE_AUTHOR("dvgt");
MODULE_DESCRIPTION("Kernel Module implemented for CSE231 Assignment-3");
```

## Run

Note that problem 3 has a custom `Makefile` to compile the module. To compile the module, run the following command in this `./` directory:

```bash
make
```

The module can also be compiled using `makefile` in the parent directory `./..` by running:

```bash
make module
```

To load, use, and unload the module, use the following commands:

```bash
sudo insmod main.ko paran_pid=<pid>        # Load the module
sudo dmesg                                 # Display the last 10 lines of the kernel log where the output is printed
sudo rmmod main.ko                         # Unload the module
```

You can use any of the following commands to display the kernel log in a better format:

```bash
sudo dmesg | grep "<phrase>"               # Search for a phrase in the kernel log
sudo dmesg | grep "<phrase>" > log.log     # Save the output to a file
sudo dmesg | tail -n 10                    # Display the last 10 lines of the kernel log
sudo dmesg | tail -n 10 > log.log          # Save the output to a file
```