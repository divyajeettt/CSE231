# Kernel memory copy (`kernel_2d_memcpy()`)

## Management of syscalls

To implement system calls, the OS stores (*see footnotes*):

- A file containing the definitions of all syscalls (`linux-5.19.8/kernel/sys.c`)
- A list of these syscalls in a syscall table, along with their numbers (`linux-5.19.8/arch/x86/entry/syscalls/syscall_6.tbl`)

Problem 2 required us to create our own syscall (`kernel_2d_memcpy()`) that copies one 2-dimensional floating point matrix to another.

## About the solution

The following step-wise approach was followed to solve the problem:

1. Create a new syscall named `kernel_2d_memcpy()` in `linux-5.19.8/kernel/sys.c`. The following is the definition of the syscall:

```c
SYSCALL_DEFINE4(kernel_2d_memcpy, float **, source, float **, dest, int, row, int, col)
{
    while (row--)
    {
        float buffer[col];
        if (__copy_from_user(&buffer, &source[row], col*sizeof(float)))
        {
            return -EFAULT;
        }
        if (__copy_to_user(&dest[row], &buffer, col*sizeof(float)))
        {
            return -EFAULT;
        }
    }
    return 0;
}
```

2. Add the syscall to the syscall table in `linux-5.19.8/arch/x86/entry/syscalls/syscall_6.tbl`. The syscall number is 469.

```
469	common  kernel_2d_memcpy	sys_kernel_2d_memcpy
```

3. Compile the new kernel, and add it with the name `linux-AB`.
4. Store the `diff` between the old and new kernels in `./2/diff.patch`.
5. Create and run a testing program `test.c` that calls the syscall `kernel_2d_memcpy()`.

## Footnotes

The `kernel/sys.c` is (obviously) compiled during kernel compilation and the final syscall information is stored in the `bzImage` formed during compilation.
