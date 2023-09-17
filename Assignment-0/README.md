# Artix Linux Install and Setup

## Introduction

This is a guide to install and setup Artix Linux on Oracle VM VirtualBox. This guide is based on the [Artix Linux Installation Guide](https://artixlinux.org/wiki/Installation_Guide) and the [Artix Linux Handbook](https://artixlinux.org/wiki/Handbook:Contents). 

Courtesy to [Mehul Arora](https://github.com/sociallyencrypted).

## Foreword

### Writing Style

In the section `Booting the Live Environment`:

- Buttons which need to be pressed are mentioned in bold.
- Options that can be selected from a check-list/menu are mentioned in italics.
- Options that are to be selected from a slider are mentioned in square brackets.
- Options that are to be typed are given in monospace.

### Important Commands

To gain access as the root user, use the following command:

```bash
sudo su
```

To view the current directory/disk structure, use the following command:

```bash
lsblk
```

### Usage of vim

The following commands are used to navigate through vim:

```bash
vim filename    # open the file filename in vim
i               # enter insert mode
Esc             # exit insert mode
:wq             # save and quit
```

## Installation and Setup

### Booting the Live Environment

Follow the steps below to boot the live environment of Artix Linux:

1. Download the ISO file `artix-base-runit-20220713-x86_64` from the [Artix Linux Download Page](https://artixlinux.org/download/).
2. Open VirtualBox.
3. Click **New** to create a new Virtual Machine. Select the following configurations under the following screens (keep clicking **Next** after every step, duh):
   - Name and Operating System:
     - Name: `Artix`
     - Type: `Linux`
     - Version: `Arch Linux (64-bit)`
   - [Memory Size: 2048 MB]
   - Hard Disk:
     - *Create a virtual hard disk now* $\rightarrow$ *VDI (VirualBox Disk Image)* $\rightarrow$ *Dynamically allocated* $\rightarrow$ [Select size: 20 GB] $\rightarrow$ **Create**
4. A new virtual machine is created. Click on the newly created virtual machine and select **Settings**. Select the following options:
   - **System** $\rightarrow$ *enable EFI*
   - **Display** $\rightarrow$ [Video memory: 128 MB]
   - **Storage** $\rightarrow$ *Controller: IDE* $\rightarrow$ **Add optical drive** $\rightarrow$ **Add disk image** $\rightarrow$ *Select the ISO file downloaded in step 1* $\rightarrow$ **Choose**
5. Boot the virtual machine using the **Start** button.
6. Now you are inside Artix. Select the CD DVD ISO option and Enter. The screen should be filled with output.

You can now proceed to partition the disk and compile the custom Artix Linux.

### Partitioning the Disk

The CD should be partitioned into two drivers We only manipulate the sda hard disk (approx. 20 GB as selected)

Use the following commands to partition the disk.

```bash
sudo su            # switch to root user
cfdisk /dev/sda    # pointer to hard disk sda
```

In the new window that appears:

- Select Label Type: `gpt`
- **New** $\rightarrow$ [Partition Size: 512 MB]
- **Down Arrow Key** $\rightarrow$ *free space* $\rightarrow$ (Do this for total - 512 MB)

This should create two partitions, `sda1` and `sda2`. Go to `sda1`: *type* $\rightarrow$ `EFI System` $\rightarrow$ **Write** $\rightarrow$ **Quit**.

### Making the File System Allocation Table

Use the following commands to make the file system allocation table.

```bash
lsblk
mkfs.fat -F32 /dev/sda1          # make file system allocation table for sda1
mkfs.ext4 /dev/sda2              # make file system allocation table for sda2
mount /dev/sda2 /mnt             # mount sda2 to /mnt
mkdir -p /mnt/boot/efi           # create a directory boot in /mnt
mount /dev/sda1 /mnt/boot/efi    # mount sda1 to /mnt/boot/efi
lsblk
```

There should be some new changes in the structure.

### Compiling the Custom Artix Linux

Use the following commands to compile the custom Artix Linux.

```bash
basestrap /mnt base base-devel elogind-runit linux linux-firmware vim
fstabgen -U /mnt >> /mnt/etc/fstab

ls /mnt             # To check the mounted directories
arch-chroot /mnt    # switch to the new root directory
sudo su

# bs should be set to half of the RAM size
dd if=/dev/zero of=/swapfile bs=1G count=2 status=progress

mkswap /swapfile
chmod 600 /swapfile
mkswap /swapfile
```

```bash
vim /etc/fstab
# Insert the following line of (tab-separated) text in the file:
/swapfile   none    swap    default    0   0
# Save and Exit
```

```bash
ln -sf /ur/share/zoneinfo/Asia/Kolkata /etc/localtime
hwclock --systohc
```

```bash
vim /etc/locale.gen
# Scroll down to find the following line and uncomment it:
en_US.UTF-8 UTF-8
# Save and Exit
```

```bash
locale-gen
```

```bash
vim /etc/locale.conf
# Insert the following line of text in the file:
LANG=en_US.UTF-8
# Save and Exit
```

```bash
vim /etc/hostname
# Insert the following line of text in the file:
dvgt # or whatever you want
# Save and Exit
```

```bash
vim /etc/hosts
# Insert the following lines of text in the file:
127.0.0.1   localhost
::1         localhost
127.0.1.1   dvgt.localdomain    dvgt
# Save and Exit
```

```bash
# Install packages using the pacman package manager
pacman -S grub efibootmgr networkmanager networkmanager-runit network-manager-applet

grub-install --target=x86_64-efi --efi-directory=/boot/efi --bootloader-id=GRUB

grub-mkconfig -o /boot/grub/grub.cfg

ls run
ls run/runit
ls /etc/runit/sv

passwd         # set root password (should be replaced with your password)
useradd -mG wheel -s /bin/bash dvgt
passwd dvgt    # set dvgt password

EDITOR=vim visudo
# uncomment the line with
wheel all (all:all) all
# Save and Exit
```

Now, shut fown the Virtual Machine and go to **Settings**. Uncheck *System Optical* and **Start** again.

```bash
sudo su
pacman -S neofetch
ln -s /etc/runit/sv/NetworkManager /run/runit/service
reboot
# The system will restart
pacman -Syu    # This will update the system
```

You now must have a working Artix Linux system.

### Enabling Arch Linux Repositories

To enable Arch Linux repositories, use the following commands.

```bash
sudo su
pacman -Syu
```

```bash
vim /etc/pacman.conf

# Add the following lines to the end of the file:

[universe]
Server = https://universe.artixlinux.org/$arch
Server = https://mirror1.artixlinux.org/universe/$arch
Server = https://mirror.pascalpuffke.de/artix-universe/$arch
Server = https://artixlinux.qontinuum.space/artixlinux/universe/os/$arch
Server = https://mirror1.cl.netactuate.com/artix/universe/$arch
Server = https://ftp.crifo.org/artix-universe/

# Save and Exit
```

```bash
pacman -S artix-archlinux-support
pacman -Syu
```

```bash
vim /etc/pacman.conf

# Add the following lines to the end of the file:

[extra]
Include = /etc/pacman.d/mirrorlist-arch
[community]
Include = /etc/pacman.d/mirrorlist-arch
[multilib]
Include = /etc/pacman.d/mirrorlist-arch

# Save and Exit
```

```bash
pacman -S binutils elfutils gcc gdb make automake autoconf yasm git github-cli xz tar vim
pacman -Syu
```
