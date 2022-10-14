# oshell

## About oshell

oshell is an interactive [Shell](https://en.wikipedia.org/wiki/Shell_(computing)) created to mimic some functionalities of the Artix [Linux](https://en.wikipedia.org/wiki/Linux) Shell.

*<b>Note:</b> oshell can only run on Linux-based systems (developed on [Artix Linux](https://artixlinux.org/))*

## Some Key Features

### Functionalities

oshell completely mirrors the functionality of the implemented commands on the Linux Shell (at least with respect to the handled options). From the prompt showing the current directory to name of the root user, to the number of spaces in outputs produced by `cat`, oshell (almost) completely mimics the Linux Shell experience.

### Flexibility

Options (aka flags) can be passed anywhere in the command (according to the syntax allowed by the Linux Shell). For example,

```console
[dvgt@oshell Assignment-1]$ rm -rv ./dir1/dir2
```

is equivalent to

```console
[dvgt@oshell Assignment-1]$ rm -v ./dir1/dir2 -r
```

### Errors handled

The following errors and edge cases are handled by oshell:

- Invalid command passed to the shell
- Invalid option passed to ANY command
- Extra options passed to ANY command
- Extra arguments passed to ANY command
- Missing required arguments by ANY command
- File-Not-Found/Directory-Not-Found or File-Exisits/Directory-Exists types of errors
- Errors arising at run-time due to `fork()`, `execv()`, and/or `pthread_create()` are reported through `perror()`

The following possibilities of vulnerabilities are also handled:

- Protected against input [buffer overflows](https://en.wikipedia.org/wiki/Buffer_overflow).
- Only the mentioned list of commands can be executed through the `system()` API call, to protect the system against injection-related vulnerabilities.
- Protected against EOF Errors, i.e. when the input stream is forcefully shut down (for example, CTRL+D). In that case, oshell logs out just like the Artix Linux Terminal.

## Supported commands

oshell supports the undermentioned list of commands (with options):

### Internal commands

These commands are written and handled in the `main.c` file itself. These include:

#### cd

The `cd` command allows the user to change the current working directory of the Shell. It supports the following options:

- `-L`: Forces symbolic links to be followed (default)
- `-P`: Use the physical directory structure without following symbolic links

Examples:

```console
[dvgt@oshell Assignment-1]$ cd ..
[dvgt@oshell CSE231]$ cd
[dvgt@oshell CSE231]$ cd ./../CSE201/Refresher-Module
[dvgt@oshell Refresher-Module]$
```

#### echo

The `echo` command writes its arguments to standard output followed by a newline. It supports the following options:

- `-n`: Does not append a trailing newline
- `-e`: Enables interpretation of backslash-escapes

Examples:

```console
[dvgt@oshell Assignment-1]$ echo oh my god, oshell works
oh my god, oshell works
[dvgt@oshell Assignment-1]$ echo -n all hail oshell
all hail oshell[dvgt@oshell Assignment-1]$ echo

[dvgt@oshell Assignment-1]$ echo -e ABC\tXYZ
ABC    XYZ
```

*<b>Assumption:</b> The options given to the `echo` command (if any) will ONLY be given as the first argument. All subsequent options will be treated as text literals.*

#### pwd

The `pwd` command simply displays the current working directory of the Shell. It supports the following options:

- `-L`: Print the value of `$PWD` if it names the current working directory (default)
- `-P`: Print the physical directory without any symbolic links

Examples:

```console
[dvgt@oshell Assignment-1]$ pwd
/home/dvgt/CSE231/Assignment-1
[dvgt@oshell Assignment-1]$ cd ..
[dvgt@oshell CSE231]$ pwd -L
/home/dvgt/CSE231/
```

### External commands

These commands are written and handled in separate executables (named according to the respective command). If an `&t` follows the command and its arguments/options, the command is executed using the POSIX Pthread family of functions, i.e. `pthread_create()` and `pthread_join()`, and `system()` API calls. Otheriwse, the same command is executed using the `fork()` and `execv()` syscalls.

#### ls

The `ls` command displays a space-separated list of files and directories in the current working directory. Mentioning multiple directories with `ls` will list down the items in each directory. It supports the following options:

- `-a`: Lists down *all* files and directories, i.e., do not ignore entries starting with `.`
- `-1`: Separate the list with newlines instead of spaces

Examples:

```console
[dvgt@oshell Assignment-1]$ ls
Assignment-1.pdf  bin  makefile  README.md  src
[dvgt@oshell Assignment-1]$ ls ./bin ./src -1
./bin:
cat
clear
date
ls
main
mkdir
rm

./src:
cat.c
clear.c
date.c
ls.c
main.c
mkdir.c
rm.c
[dvgt@oshell Assignment-1]$ cd ..
[dvgt@oshell CSE231]$ ls -a &t
.  ..  Assignment-0  Assignment-1  .git  README.md
```

*<b>Assumption:</b> The output order of ls is not sorted by default.*

#### cat

The `cat` command can be used in two ways. It can be used to read the contents of a file. Mentioning multiple files with `cat` will display the contents of each file. However, if no arguments are given, it reads from `stdin` and writes to `stdout` until `EOF` is found. It supports the following options:

- `-n`: Enumerate all output lines
- `-E`: Write `$` at the end of each line

Examples:

```console
[dvgt@oshell Assignment-1]$ cat -n
oh my god, oshell works
     1  oh my god, oshell works
all hail oshell
     2  all hail oshell
[dvgt@oshell Assignment-1]$ cat -E sample.txt demo.txt &t
This file does not exist$
But this is a sample example, so meh$
$
This is demo.txt speaking$
```

#### date

The `date` command is used to display the current system date and time. By defualt, it displays the localtime. It supports the following options:

- `-I`: Output date in ISO-8601 format
- `-R`: Output date in RFC-5322 format
- `-u`: Output the Coordinated Universal Time (UTC)

Examples:

```console
[dvgt@oshell Assignment-1]$ date
Fri Oct 14 12:05:48 PM IST 2022
[dvgt@oshell Assignment-1]$ date -I &t
2022-10-14
[dvgt@oshell Assignment-1]$ date -R
Fri, 14 Oct 2022 12:07:00 +0530
[dvgt@oshell Assignment-1]$ date -u &t
Fri Oct 14 06:37:33 AM UTC 2022
```

#### rm

The `rm` command is used to remove files from the system. Mentioning multiple items with `rm` will remove all listed items from the system. It supports the following options:

- `-r`: Remove directories and their contents recursively
- `-v`: Output a message for each deleted file/directory

Examples:

```console
[dvgt@oshell Assignment-1]$ rm makefile
[dvgt@oshell Assignment-1]$ ls
Assignment-1.pdf  bin  README.md  src
[dvgt@oshell Assignment-1]$ rm -rv ./src &t
removed './src/cat.c'
removed './src/date.c'
removed './src/rm.c'
removed './src/clear.c'
removed './src/ls.c'
removed './src/main.c'
removed './src/mkdir.c'
removed directory './src'
```

#### mkdir

The `mdkir` command is used to create directories. Mentioning multiple items with `mdkir` will create all mentioned directories. It supports the following options:

- `-p`: Does not produce an error if the directory exists, and make parent directories as needed
- `-v`: Output a message for each created directory

Examples:

```console
[dvgt@oshell Assignment-1]$ mkdir /src -p
[dvgt@oshell Assignment-1]$ mkdir -p new/new/new -v &t
mkdir: created directory 'new'
mkdir: created directory 'new/new'
mkdir: created directory 'new/new/new'
[dvgt@oshell Assignment-1]$ ls
Assignment-1.pdf  bin  makefile  new  README.md  src
```

### Extra commands

To make this a better project, some extra commands have also been added to oshell. These include:

#### clear

The `clear` command clears the Shell screen. It does not support any options. It is an external command, and can be executed with or without the `&t` syntax defined in the Assignment. It's simple usage is:

```console
[dvgt@oshell Assignment-1]$ clear
```

#### type

The `type` command is used to check whether a command is an internal or external command. Examples:

```console
[dvgt@oshell Assignment-1]$ type cd
cd is a shell builtin
[dvgt@oshell Assignment-1]$ type date
date is /home/dvgt/CSE231/Assignment-1/bin/date
[dvgt@oshell Assignment-1]$ type mkdir
mkdir is hashed (/home/dvgt/CSE231/Assignment-1/bin/mkdir)
```

*<b>Assumption:</b> Some external commands like `mkdir` and `rm` are displayed as 'hashed' to more accurately "mimic" the Linux Shell's behaviour. In reality, these files are simple executables located in the `./bin` directory.*

#### exit

The `exit` command simply stops the execution of the Shell, i.e., exits it. Example:

```console
[dvgt@oshell Assignment-1]$ exit
logout
oshell-2.3.1 (tty1)
[dvgt@artix Assignment-1]$
```

#### help

The `help` command displays some help text for the specified command, along with the options it supports.

### Hidden command

A (hidden) easter-egg command has also been coded into oshell. *For the keen minds, it is a word that I use very often!*

## Run

To run the shell, navigate to the directory Assignment-1:

```console
cd Assignment-1
```

To build the binary files, run:

```console
make
```

Finally, to start the Shell, execute:

```console
./bin/main
```

## References

- [<b>CSE231</b> Lecture Slides: *Dr Sambuddho Chakravarty*](https://drive.google.com/file/d/15927VKp8q1xwLvs28I4lgDyLF0XGcrXk/view)
- [Manual Page: `fork()`](https://man7.org/linux/man-pages/man2/fork.2.html)
- [Manual Page: `exec()`](https://man7.org/linux/man-pages/man3/exec.3.html)
- [Manual Page: `wait()`](https://man7.org/linux/man-pages/man2/waitpid.2.html)
- [Manual Page: `pthread_create()`](https://man7.org/linux/man-pages/man3/pthread_create.3.html)
- [Manual Page: `pthread_join()`](https://man7.org/linux/man-pages/man3/pthread_join.3.html)
- [Manual Page: `system()`](https://man7.org/linux/man-pages/man3/system.3.html)
