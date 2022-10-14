# oshell

## About oshell

oshell is an interactive [Shell](https://en.wikipedia.org/wiki/Shell_(computing)) created to mimic some functionalities of the [Linux](https://en.wikipedia.org/wiki/Linux) Shell. It aims to deepen the understanding of the use of [System Calls](https://en.wikipedia.org/wiki/System_call) like `fork()`, `execl()`, and `wait()` and the use of API function calls like `pthread_create()` and `system()`.

*<b>Note:</b> oshell can only run on Linux-based systems (developed on [Artix Linux](https://artixlinux.org/))*

## Some Key Features

### Functionalities

oshell completely mirrors the functionality of the implemented commands on the Linux Shell (at least with respect to the handled options). From the current directory prompt to the number of spaces in outputs produced by `cat`, oshell completely mimics the Linux Shell experience.

### Flexibility

Options (aka flags) can be passed anywhere in the command (according to the syntax allowed by the Linux Shell). For example, \
`rm -rv ./dir1/dir2` is equivalent to `rm -v ./dir1/dir2 -r`.

### Support for multiple arguments

Some commands support multiple arguments, i.e., oshell allows you to create multiple directories, remove multiple files/directories, and read multiple files using a single command. This is an implication of the supported functionalities.

### Errors handled

The following cases of errors are handled by oshell:
- Invalid command passed to the shell
- Invalid option passed to a command
- Missing required arguments by a command
- File-Not-Found or File-Exisits/Directory-Exists types of errors
- Errors arising at run-time due to `fork()`, `execv()`, and/or `pthread_create()` are reported through `perror()`

## Supported commands

oshell supports the undermentioned list of Shell (with options):

### Internal commands

These commands are written and handled in the `main.c` file itself. These include:

### External commands

These commands are written and handled in separate executables (named according to the respective command). If the command ends with `&t`, the command is executed using the `pthread_create()` and `system()` API calls. Otheriwse, the same command is executed using the `fork()` and `execv()`system calls.

### Extra commands

To make this a better project, some extra commands have also been added to oshell. These inlcude:

### Hidden command

A (hidden) easter-egg command has been coded into oshell. *For the keen minds, it is a word that I use very often!*

## Run
